# CSE321 : Operating System

This course provides a general understanding of the principles and concepts governing the functions of operating systems and acquaints students with the state-of-the-art approaches that make the design, implementation, and operation of complex operating systems possible. The core of the course contains concurrent programming (threads and synchronization), inter-process communication, process and thread management, storage and resource management and communication, and an analysis on security and protection.

# [Lab](https://drive.google.com/drive/folders/15jnsGJg7MzduETba6kqlpbKTwfMwyda5)
# [Resources](https://drive.google.com/drive/folders/1gCcrq_xkHRbx9HU8-1Cwa2NOi7JqocKX)

#[Assignment1](https://drive.google.com/drive/folders/10_xQHLade6T-io3eVNH6XnS7hGzsbr6D?usp=sharing)
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

### [Python Threading](https://www.youtube.com/watch?v=A_Z1lgZLSNc)

### [Python Threading](https://www.youtube.com/watch?v=A_Z1lgZLSNc)

# CPU Scheduling in Operating Systems

## 1. Basic Concepts
- **Goal**: Maximize CPU utilization with multiprogramming.
- **CPU-I/O Burst Cycle**: Alternates between CPU execution and I/O wait.
- **CPU Scheduler**: Selects a process from the ready queue and assigns it to the CPU.
  - Implemented using:
    - FIFO Queue
    - Priority Queue
    - Tree
    - Unordered Linked List
- **Scheduling Decisions Occur When:**
  1. A process switches from **running → waiting** (I/O request).
  2. A process switches from **running → ready** (interrupt occurs).
  3. A process switches from **waiting → ready** (I/O completes).
  4. A process terminates.
- **Non-preemptive Scheduling**: Happens under cases (1) and (4).
- **Preemptive Scheduling**: Happens under cases (2) and (3).

## 2. Scheduling Criteria
1. **CPU Utilization** - Keep the CPU as busy as possible.
2. **Throughput** - Number of completed processes per time unit.
3. **Turnaround Time** - Total time from process submission to completion.
   - **Formula:**
     ```
     Turnaround Time = Completion Time - Arrival Time
     ```
4. **Waiting Time** - Time spent in the ready queue.
   - **Formula:**
     ```
     Waiting Time = Turnaround Time - Burst Time
     ```
5. **Response Time** - Time from request submission to first response.
   - **Formula:**
     ```
     Response Time = First Response Time - Arrival Time
     ```

## 3. CPU Scheduling Algorithms

### 3.1 First Come First Serve (FCFS)
- **Processes are executed in order of arrival.**
- **Non-preemptive**.
- **Causes the "convoy effect"** (short processes wait for long ones).

Example:
| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |
|---------|--------------|------------|----------------|-----------------|--------------|
| P1      | 0            | 8          | 8              | 8               | 0            |
| P2      | 1            | 4          | 12             | 11              | 7            |
| P3      | 2            | 9          | 21             | 19              | 10           |
| P4      | 3            | 5          | 26             | 23              | 18           |

---

### 3.2 Shortest Job First (SJF)
- **Shortest process gets executed first.**
- **Two types:**
  - **Non-preemptive**: Once a process starts, it runs till completion.
  - **Preemptive (SRTF - Shortest Remaining Time First)**: New shorter processes can preempt running ones.
- **Optimal for waiting time** but requires **predicting burst time.**

---

### 3.3 Priority Scheduling
- **Each process has a priority.**
- **Process with the highest priority (smallest number) executes first.**
- **Two types:**
  - **Preemptive**: Higher priority process preempts the running process.
  - **Non-preemptive**: CPU assigned only after the current process completes.
- **Issue:** Starvation (low-priority processes may never execute).
- **Solution:** Aging (increase priority over time).

---

### 3.4 Round Robin (RR)
- **Each process gets a fixed time quantum (q)** (e.g., 10–100ms).
- **Preemptive:** If a process doesn’t finish in `q`, it moves to the end of the queue.
- **Good for time-sharing systems** but has **high context-switching overhead**.

Example (q=4, Gantt Chart):
```
P1 | P2 | P3 | P4 | P1 | P3 | P4 | P3
0   4    8   12   16   20   24   25   26
```

---

### 3.5 Multilevel Queue Scheduling
- **Processes are categorized into separate queues (e.g., foreground, background).**
- **Each queue has its own scheduling algorithm:**
  - Foreground: **Round Robin (RR)**
  - Background: **First Come First Serve (FCFS)**
- **Queue Scheduling:**
  - **Fixed priority**: Foreground gets full priority over background.
  - **Time-slice**: Each queue gets a fixed CPU percentage.

---

### 3.6 Multilevel Feedback Queue Scheduling
- **Processes move between queues based on behavior.**
- **Rules:**
  - If a process uses too much CPU, it moves **to a lower-priority queue**.
  - If a process waits too long, it moves **to a higher-priority queue**.
- **Example Setup:**
  1. **Queue 0** (Priority 0, **RR q=8**)
  2. **Queue 1** (Priority 1, **RR q=16**)
  3. **Queue 2** (Priority 2, **FCFS**)

---

## 4. Comparison of Scheduling Algorithms

| Algorithm            | Preemptive | Starvation? | Turnaround Time | Waiting Time | Response Time | Fairness |
|----------------------|-----------|-------------|----------------|--------------|--------------|-----------|
| **FCFS**            | No        | No          | High           | High         | High         | Low       |
| **SJF**             | Optional  | Yes         | Low            | Low          | Medium       | Low       |
| **Priority**        | Optional  | Yes         | Medium         | Medium       | Medium       | Low       |
| **Round Robin**     | Yes       | No          | Medium         | Medium       | Low          | High      |
| **Multilevel Queue**| Yes       | Yes         | Medium         | Medium       | Medium       | Low       |
| **Multilevel FBQ**  | Yes       | No          | Low            | Low          | Low          | High      |

---


- **FCFS**: Simple but inefficient due to **convoy effect**.
- **SJF**: Optimal for **waiting time** but requires burst time prediction.
- **Priority Scheduling**: **Efficient** but **causes starvation**.
- **Round Robin**: **Good for time-sharing** but **high context switching overhead**.
- **Multilevel Queue**: Separates process types but **fixed priority can cause starvation**.
- **Multilevel Feedback Queue**: **Most flexible**, but **complex to implement**.

---

