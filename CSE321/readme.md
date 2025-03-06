# CSE321 : Operating System

This course provides a general understanding of the principles and concepts governing the functions of operating systems and acquaints students with the state-of-the-art approaches that make the design, implementation, and operation of complex operating systems possible. The core of the course contains concurrent programming (threads and synchronization), inter-process communication, process and thread management, storage and resource management and communication, and an analysis on security and protection.


# [Resources](https://drive.google.com/drive/folders/1gCcrq_xkHRbx9HU8-1Cwa2NOi7JqocKX)


# Testing System Calls on Linux

This project demonstrates various **system calls** available on Linux, including **process control, file operations, inter-process communication (IPC), shared memory, and file permissions**.

## 🛠 System Calls Tested

### **Process Management**
- `fork()` - Creates a child process.
- `exit()` - Terminates a process.
- `wait()` - Parent process waits for child termination.
- `getpid()` - Retrieves process ID.
- `alarm()` & `sleep()` - Timer and delays.

### **File Operations**
- `open()` - Opens a file.
- `read()` - Reads from a file.
- `write()` - Writes to a file.
- `close()` - Closes a file.

### **Inter-Process Communication (IPC)**
- `pipe()` - Creates a pipe for communication between processes.
- `shm_open()` & `mmap()` - Shared memory usage.

### **File Permissions**
- `chmod()` - Changes file permissions.
- `umask()` - Sets default file creation mask.
- `chown()` - Changes file ownership (requires root privileges).


## 📜 Code Implementation

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

#define SHM_NAME "/test_shm"
#define SHM_SIZE 4096

int main() {
    pid_t pid;
    int status;

    // fork()
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) { // Child process
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        int fd = open("testfile.txt", O_CREAT | O_WRONLY, 0644);
        if (fd < 0) {
            perror("open failed");
            exit(1);
        }
        write(fd, "Hello, Linux system calls!\n", 27);
        close(fd);
        alarm(2);
        sleep(3);
        exit(0);
    } else { // Parent process
        printf("Parent process: PID = %d\n", getpid());
        wait(&status);
        printf("Child exited with status %d\n", WEXITSTATUS(status));

        // pipe()
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe failed");
            exit(1);
        }

        pid_t pipe_pid = fork();
        if (pipe_pid == 0) { // Child process for pipe
            close(pipefd[0]);
            char msg[] = "Hello from child through pipe!";
            write(pipefd[1], msg, strlen(msg));
            close(pipefd[1]);
            exit(0);
        } else { // Parent reads from pipe
            close(pipefd[1]);
            char buffer[50];
            read(pipefd[0], buffer, sizeof(buffer));
            printf("Parent received from pipe: %s\n", buffer);
            close(pipefd[0]);
        }

        // shm_open() and mmap()
        int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        if (shm_fd < 0) {
            perror("shm_open failed");
            exit(1);
        }
        ftruncate(shm_fd, SHM_SIZE);
        void *shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (shm_ptr == MAP_FAILED) {
            perror("mmap failed");
            exit(1);
        }
        sprintf((char *)shm_ptr, "Shared memory message!");
        printf("Shared memory written: %s\n", (char *)shm_ptr);

        chmod("testfile.txt", 0600);
        umask(0027);
        shm_unlink(SHM_NAME);
        unlink("testfile.txt");
    }

    return 0;
}
```

 
# Threading

![Python Threading](https://www.youtube.com/watch?v=A_Z1lgZLSNc)
