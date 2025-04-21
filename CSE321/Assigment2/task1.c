#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int *fibonacci = NULL;
int n = 0;
int *search_indices = NULL;
int search_count = 0;

sem_t fibonacci_ready;

void* generate_fibonacci(void *arg) {
    fibonacci = (int*) malloc((n + 1) * sizeof(int));
    if (fibonacci == NULL) {
        printf("Memory allocation failed.\n");
        pthread_exit(NULL);
    }

    fibonacci[0] = 0;
    if (n > 0) fibonacci[1] = 1;

    for (int i = 2; i <= n; i++) {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }

    sem_post(&fibonacci_ready);
    pthread_exit(NULL);
}

void* search_fibonacci(void *arg) {
    sem_wait(&fibonacci_ready);

    for (int i = 0; i < search_count; i++) {
        int idx = search_indices[i];
        if (idx >= 0 && idx <= n) {
            printf("result of search #%d = %d\n", i + 1, fibonacci[idx]);
        } else {
            printf("result of search #%d = -1\n", i + 1);
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t fibonacci_thread, search_thread;

    sem_init(&fibonacci_ready, 0, 0);

    printf("Enter the term of fibonacci sequence:\n");
    scanf("%d", &n);

    pthread_create(&fibonacci_thread, NULL, generate_fibonacci, NULL);
    pthread_join(fibonacci_thread, NULL);
    printf("How many numbers you are willing to search?:\n");
    scanf("%d", &search_count);

    search_indices = (int*) malloc(search_count * sizeof(int));
    if (search_indices == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < search_count; i++) {
        printf("Enter search %d:\n", i + 1);
        scanf("%d", &search_indices[i]);
    }

    for (int i = 0; i <= n; i++) {
        printf("a[%d] = %d\n", i, fibonacci[i]);
    }

    pthread_create(&search_thread, NULL, search_fibonacci, NULL);
    pthread_join(search_thread, NULL);

    sem_destroy(&fibonacci_ready);

    return 0;
}

