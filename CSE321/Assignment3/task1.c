#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SHM_SIZE  sizeof(struct shared)

struct shared {
    char sel[100];
    int b;
};

int main() {
    int shmid, pipefd[2];
    struct shared *shm;
    pid_t pid;
    char input[100];
    char pipe_buf[100];

    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    shm = (struct shared *)shmat(shmid, NULL, 0);
    if (shm == (struct shared *)-1) {
        perror("shmat");
        exit(1);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    printf("Provide Your Input From Given Options:\n\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    strncpy(shm->sel, input, sizeof(shm->sel));
    shm->b = 1000;

    printf("Your selection: %s\n\n", shm->sel);

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        int amount;

        shm = (struct shared *)shmat(shmid, NULL, 0);
        if (shm == (struct shared *)-1) {
            perror("shmat");
            exit(1);
        }

        if (strcmp(shm->sel, "a") == 0) {
            printf("Enter amount to be added:\n");
            scanf("%d", &amount);
            if (amount > 0) {
                shm->b += amount;
                printf("Balance added successfully\n");
                printf("Updated balance after addition:\n%d\n", shm->b);
            } else {
                printf("Adding failed, Invalid amount\n");
            }
        } else if (strcmp(shm->sel, "w") == 0) {
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &amount);
            if (amount > 0 && amount <= shm->b) {
                shm->b -= amount;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal:\n%d\n", shm->b);
            } else {
                printf("Withdrawal failed, Invalid amount\n");
            }
        } else if (strcmp(shm->sel, "c") == 0) {
            printf("Your current balance is:\n%d\n", shm->b);
        } else {
            printf("Invalid selection\n");
        }

        write(pipefd[1], "Thank you for using", 19);
        close(pipefd[1]);

        shmdt(shm);
        exit(0);
    } else {
        wait(NULL);

        read(pipefd[0], pipe_buf, sizeof(pipe_buf));
        printf("%s\n", pipe_buf);
        close(pipefd[0]);

        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
