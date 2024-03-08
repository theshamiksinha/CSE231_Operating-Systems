#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <dispatch/dispatch.h>
#include <unistd.h>

dispatch_semaphore_t bridge_mutex;
int left_cars, right_cars;
dispatch_semaphore_t lock;

void passing(int dir, int car_id, pthread_t thread_id)
{
    if (dir == 0)
    {
        printf("Car %d from the left, Thread ID: %lu, is on the bridge.\n", car_id, (unsigned long)thread_id);
    }
    else
    {
        printf("Car %d from the right, Thread ID: %lu, is on the bridge.\n", car_id, (unsigned long)thread_id);
    }
    sleep(1); // Simulating time taken to cross the bridge

    dispatch_semaphore_signal(bridge_mutex);
}

void *left(void *args)
{
    int car_id = *((int *)args);
    pthread_t thread_id = pthread_self(); // Get the thread ID
    passing(0, car_id, thread_id);
    return NULL;
}

void *right(void *args)
{
    int car_id = *((int *)args);
    pthread_t thread_id = pthread_self(); // Get the thread ID
    passing(1, car_id, thread_id);
    return NULL;
}

int main()
{
    pthread_t left_threads[100000], right_threads[100000];
    int left_args[5], right_args[5];

    bridge_mutex = dispatch_semaphore_create(4);

    printf("Enter the number of cars on the left side: ");
    scanf("%d", &left_cars);
    printf("Enter the number of cars on the right side: ");
    scanf("%d", &right_cars);

    for (int i = 0; i < left_cars; i++)
    {
        left_args[i] = i + 1;
        pthread_create(&left_threads[i], NULL, left, (void *)&left_args[i]);
        dispatch_semaphore_wait(bridge_mutex, DISPATCH_TIME_FOREVER);
    }

    for (int i = 0; i < left_cars; i++)
    {
        pthread_join(left_threads[i], NULL);
    }

    for (int i = 0; i < right_cars; i++)
    {
        right_args[i] = i + 1;
        pthread_create(&right_threads[i], NULL, right, (void *)&right_args[i]);
        dispatch_semaphore_wait(bridge_mutex, DISPATCH_TIME_FOREVER);
    }

    for (int i = 0; i < right_cars; i++)
    {
        pthread_join(right_threads[i], NULL);
    }

    return 0;
}
