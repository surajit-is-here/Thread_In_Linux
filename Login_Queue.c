// Implementation of Login Queue using Threads and Semaphore..

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define n 16    //Number of users
sem_t semaphore;
pthread_mutex_t mutex;

void *routine(void *args)
{
    printf("(%d) waiting in login queue\n", *(int *)args);
    sem_wait(&semaphore);
    printf("(%d) logged in....welcome\n", *(int *)args);
    sleep(rand() % 5 + 1);
    printf("(%d) logged out...Thank You\n", *(int *)args);
    sem_post(&semaphore);
    free(args);
}

int main()
{
    pthread_t th[n];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaphore, 0, 10);    //Number of slots is 10

    for (int i = 0; i < n; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
            perror("Failed to create thread\n");
    }

    for (int i = 0; i < n; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread\n");
    }

    sem_destroy(&semaphore);
    pthread_mutex_destroy(&mutex);
}