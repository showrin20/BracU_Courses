#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define STU_NUM 10
#define NUM_CHAIRS 3

sem_t wake_st;
sem_t ready_student;
sem_t get_chair;        
int waiting_students = 0;
int total_served_students = 0;

pthread_mutex_t serve_mutex;

void* student(void* arg) {
    int id = *((int*)arg);
    sleep(rand() % 3);

    sem_wait(&get_chair);
    if (waiting_students < NUM_CHAIRS) {
        waiting_students++;
        printf("Student %d started waiting for consultation\n", id);
        printf("Number of students now waiting: %d\n", waiting_students);
        sem_post(&get_chair);

        sem_post(&ready_student);
        sem_wait(&wake_st);

        pthread_mutex_lock(&serve_mutex);
        printf("ST giving consultation\n");
        printf("Student %d is getting consultation\n", id);
        sleep(1);
        printf("Student %d finished getting consultation and left\n", id);
        total_served_students++;
        printf("Number of served students: %d\n", total_served_students);
        pthread_mutex_unlock(&serve_mutex);
    } else {
        printf("No chairs remaining in lobby. Student %d Leaving.....\n", id);
        sem_post(&get_chair);
    }

    free(arg);
    pthread_exit(NULL);
}

void* st_thread(void* arg) {
    while (total_served_students < STU_NUM) {
        sem_wait(&ready_student);
        sem_wait(&get_chair);

        if (waiting_students > 0) {
            waiting_students--;
            printf("A waiting student started getting consultation\n");
            printf("Number of students now waiting: %d\n", waiting_students);
        }

        sem_post(&get_chair);
        sem_post(&wake_st);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t students[STU_NUM];
    pthread_t st;

    sem_init(&wake_st, 0, 0);
    sem_init(&ready_student, 0, 0);
    sem_init(&get_chair, 0, 1);
    pthread_mutex_init(&serve_mutex, NULL);

    pthread_create(&st, NULL, st_thread, NULL);

    for (int i = 0; i < STU_NUM; i++) {
        int* id = malloc(sizeof(int)); #memory allocate 
        *id = i;
        pthread_create(&students[i], NULL, student, id);
    }

    for (int i = 0; i < STU_NUM; i++) {
        pthread_join(students[i], NULL);
    }

    pthread_join(st, NULL);

    sem_destroy(&wake_st);
    sem_destroy(&ready_student);
    sem_destroy(&get_chair);
    pthread_mutex_destroy(&serve_mutex);

    return 0;
}

