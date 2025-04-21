#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/types.h>

struct msg_struc {
    long int type;
    char txt[6];
};

int main() {
    int massage_id;
    struct msg_struc message;
    pid_t pid1, pid2;
    char workspace[100];

    massage_id = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (massage_id < 0) {
        perror("msgget");
        exit(1);
    }

    printf("Please enter the workspace name:\n");
    fgets(workspace, sizeof(workspace), stdin);
    workspace[strcspn(workspace, "\n")] = 0;

    if (strcmp(workspace, "cse321") != 0) {
        printf("Invalid workspace name\n");
        msgctl(massage_id, IPC_RMID, NULL);
        return 0;
    }

    message.type = 1;
    strncpy(message.txt, workspace, sizeof(message.txt));
    if (msgsnd(massage_id, &message, sizeof(message.txt), 0) < 0) {
        perror("msgsnd");
        exit(1);
    }
    printf("Workspace name sent to otp generator from log in: %s\n\n", message.txt);

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {
        if (msgrcv(massage_id, &message, sizeof(message.txt), 1, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        printf("OTP generator received workspace name from log in: %s\n\n", message.txt);

        int otp = getpid();
        snprintf(message.txt, sizeof(message.txt), "%d", otp);

        message.type = 2;
        if (msgsnd(massage_id, &message, sizeof(message.txt), 0) < 0) {
            perror("msgsnd");
            exit(1);
        }
        printf("OTP sent to log in from OTP generator: %s\n", message.txt);

        message.type = 3;
        if (msgsnd(massage_id, &message, sizeof(message.txt), 0) < 0) {
            perror("msgsnd");
            exit(1);
        }
        printf("OTP sent to mail from OTP generator: %s\n", message.txt);

        pid2 = fork();
        if (pid2 < 0) {
            perror("fork");
            exit(1);
        }

        if (pid2 == 0) {
            if (msgrcv(massage_id, &message, sizeof(message.txt), 3, 0) < 0) {
                perror("msgrcv");
                exit(1);
            }
            printf("Mail received OTP from OTP generator: %s\n", message.txt);

            message.type = 4;
            if (msgsnd(massage_id, &message, sizeof(message.txt), 0) < 0) {
                perror("msgsnd");
                exit(1);
            }
            printf("OTP sent to log in from mail: %s\n", message.txt);

            exit(0);
        } else {
            wait(NULL);
            exit(0);
        }
    } else {
        wait(NULL);

        if (msgrcv(massage_id, &message, sizeof(message.txt), 2, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        char otp1[6];
        strncpy(otp1, message.txt, sizeof(otp1));
        printf("Log in received OTP from OTP generator: %s\n", otp1);

        if (msgrcv(massage_id, &message, sizeof(message.txt), 4, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        printf("Log in received OTP from mail: %s\n", message.txt);

        if (strcmp(otp1, message.txt) == 0) {
            printf("OTP Verified\n");
        } else {
            printf("OTP Incorrect\n");
        }

        msgctl(massage_id, IPC_RMID, NULL);
    }

    return 0;
}
