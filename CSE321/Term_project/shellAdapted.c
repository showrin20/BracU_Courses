#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LEN 1024
#define MAX_ARGS 100
#define HISTORY_SIZE 100

char *history[HISTORY_SIZE];
int history_count = 0;
volatile sig_atomic_t current_child_pid = -1;

void add_to_history(char *command) {
    if (history_count < HISTORY_SIZE) {
        history[history_count++] = strdup(command);
    }
}

void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

void sigint_handler(int sig) {
    if (current_child_pid > 0) {
        kill(current_child_pid, SIGINT);
    } else {
        printf("\nUse 'exit' to quit the shell.\nsh> ");
        fflush(stdout);
    }
}

void execute_command(char *command, int *exit_status);
void execute_piped_commands(char *commands[], int num_pipes, int *exit_status);
void execute_redirect(char *args[], int input_fd, int output_fd, int *exit_status);
void parse_and_execute(char *input);

int main() {
    char input[MAX_COMMAND_LEN];
    signal(SIGINT, sigint_handler);

    while (1) {
        printf("sh> ");
        fflush(stdout);

        if (fgets(input, MAX_COMMAND_LEN, stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) continue;

        add_to_history(input);
        parse_and_execute(input);
    }

    return 0;
}

void parse_and_execute(char *input) {
    char *semicolon_cmds[MAX_ARGS];
    int num_semicolon_cmds = 0;
    char *token = strtok(input, ";");

    while (token != NULL) {
        semicolon_cmds[num_semicolon_cmds++] = token;
        token = strtok(NULL, ";");
    }

    for (int i = 0; i < num_semicolon_cmds; i++) {
        char *and_cmds[MAX_ARGS];
        int num_and_cmds = 0;
        char *and_token = strtok(semicolon_cmds[i], "&&");

        while (and_token != NULL) {
            and_cmds[num_and_cmds++] = and_token;
            and_token = strtok(NULL, "&&");
        }

        int exit_status = 0;
        for (int j = 0; j < num_and_cmds; j++) {
            execute_command(and_cmds[j], &exit_status);
            if (exit_status != 0) break;
        }
    }
}

void execute_command(char *command, int *exit_status) {
    char *args[MAX_ARGS];
    int num_args = 0;
    int input_fd = 0, output_fd = 1;

    if (strcmp(command, "exit") == 0) {
        exit(0);
    }

    if (strcmp(command, "history") == 0) {
        print_history();
        *exit_status = 0;
        return;
    }

    char *piped_commands[MAX_ARGS];
    int num_pipes = 0;
    char *pipe_token = strtok(command, "|");

    while (pipe_token != NULL) {
        piped_commands[num_pipes++] = pipe_token;
        pipe_token = strtok(NULL, "|");
    }

    if (num_pipes > 1) {
        execute_piped_commands(piped_commands, num_pipes, exit_status);
        return;
    }

    char *arg_token = strtok(piped_commands[0], " ");
    while (arg_token != NULL) {
        if (strcmp(arg_token, "<") == 0) {
            arg_token = strtok(NULL, " ");
            input_fd = open(arg_token, O_RDONLY);
        } else if (strcmp(arg_token, ">") == 0) {
            arg_token = strtok(NULL, " ");
            output_fd = open(arg_token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        } else if (strcmp(arg_token, ">>") == 0) {
            arg_token = strtok(NULL, " ");
            output_fd = open(arg_token, O_WRONLY | O_CREAT | O_APPEND, 0644);
        } else {
            args[num_args++] = arg_token;
        }
        arg_token = strtok(NULL, " ");
    }

    args[num_args] = NULL;

    if (args[0] == NULL) return;

    if (strcmp(args[0], "cd") == 0) {
        if (num_args > 1) {
            if (chdir(args[1]) != 0) {
                perror("chdir failed");
                *exit_status = 1;
            } else {
                *exit_status = 0;
            }
        } else {
            fprintf(stderr, "cd: missing argument\n");
            *exit_status = 1;
        }
        return;
    }

    execute_redirect(args, input_fd, output_fd, exit_status);
}

void execute_redirect(char *args[], int input_fd, int output_fd, int *exit_status) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        *exit_status = 1;
        return;
    } else if (pid == 0) {
        signal(SIGINT, SIG_DFL);

        if (input_fd != 0) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != 1) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else {
        current_child_pid = pid;
        int status;
        waitpid(pid, &status, 0);
        current_child_pid = -1;

        if (WIFEXITED(status)) {
            *exit_status = WEXITSTATUS(status);
        } else {
            *exit_status = 1;
        }
    }
}

void execute_piped_commands(char *commands[], int num_pipes, int *exit_status) {
    int pipes[num_pipes - 1][2];
    pid_t pids[num_pipes];

    for (int i = 0; i < num_pipes - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe failed");
            *exit_status = 1;
            return;
        }
    }

    for (int i = 0; i < num_pipes; i++) {
        char *args[MAX_ARGS];
        int num_args = 0;
        char *token = strtok(commands[i], " ");

        while (token != NULL) {
            args[num_args++] = token;
            token = strtok(NULL, " ");
        }
        args[num_args] = NULL;

        if ((pids[i] = fork()) == -1) {
            perror("Fork failed");
            *exit_status = 1;
            return;
        }

        if (pids[i] == 0) {
            signal(SIGINT, SIG_DFL);

            if (i > 0)
                dup2(pipes[i - 1][0], STDIN_FILENO);
            if (i < num_pipes - 1)
                dup2(pipes[i][1], STDOUT_FILENO);

            for (int j = 0; j < num_pipes - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            execvp(args[0], args);
            perror("execvp failed");
            exit(1);
        }
    }

    for (int i = 0; i < num_pipes - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    int final_status = 0;
    for (int i = 0; i < num_pipes; i++) {
        current_child_pid = pids[i];
        int status;
        waitpid(pids[i], &status, 0);

        if (i == num_pipes - 1 && WIFEXITED(status)) {
            final_status = WEXITSTATUS(status);
        }
    }

    current_child_pid = -1;
    *exit_status = final_status;
}
