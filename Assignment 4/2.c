#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dispatch/dispatch.h>
#include <unistd.h>

dispatch_semaphore_t mutex;
dispatch_semaphore_t car_sem;
dispatch_semaphore_t passenger_sem;
dispatch_semaphore_t mainSem;

int capacity;
int passengers;
int loaded_passengers = 0;
int passengers_to_board;
int iterations;
pthread_cond_t car_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t passenger_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t car_mutex = PTHREAD_MUTEX_INITIALIZER;

void carruns() {
    printf("The car has begun running.\n");
    printf("The car has reached its location.\n");
}

void load() {
    printf("Car is loading passengers...\n");
}

void unload() {
    printf("Car is unloading passengers...\n");
}

void board(int p) {
    printf("Passenger %d is boarding the car.\n", p);
}

void offboard(int p) {
    printf("Passenger %d is offboarding the car.\n", p);
}

void* car(void* args) {
    for (int g = 0; g < iterations; g += 1) {
        // Load passengers
        load();
        sleep(1);

        // Signal passengers to board
        dispatch_semaphore_signal(passenger_sem);

        // Wait for passengers to board
        pthread_mutex_lock(&car_mutex);

        pthread_cond_wait(&car_cond, &car_mutex);
        sleep(1);

        pthread_mutex_unlock(&car_mutex);


        // Run the car
        carruns();
        sleep(1);

        // Unload passengers
        unload();
        sleep(1);

        // Signal passengers to offboard
        dispatch_semaphore_signal(passenger_sem);

        // Wait for passengers to offboard
        pthread_mutex_lock(&car_mutex);

        pthread_cond_wait(&car_cond, &car_mutex);
        sleep(1);

        pthread_mutex_unlock(&car_mutex);
    }

    return NULL;
}

void* passenger(void* args) {
    int passenger_id = *((int*)args);

    // Board the car
    board(passenger_id);

    // Wait for the car to load
    // dispatch_semaphore_wait(passenger_sem, DISPATCH_TIME_FOREVER);


    // Signal that passenger has boarded
    pthread_mutex_lock(&car_mutex);
    pthread_cond_broadcast(&car_cond);
    pthread_mutex_unlock(&car_mutex);

    // Wait for the car to run and unload
    dispatch_semaphore_wait(passenger_sem, DISPATCH_TIME_FOREVER);

    // Offboard the car
    offboard(passenger_id);

    // Signal that passenger has offboarded
    pthread_mutex_lock(&car_mutex);

    pthread_cond_broadcast(&car_cond);

    pthread_mutex_unlock(&car_mutex);

    dispatch_semaphore_signal(mainSem);

    return NULL;
}

int main() {
    // Initialize semaphores
    mutex = dispatch_semaphore_create(1);
    car_sem = dispatch_semaphore_create(0);
    passenger_sem = dispatch_semaphore_create(0);


    printf("Enter total no. of passengers: ");
    scanf("%d", &passengers);
    printf("Enter capacity of passengers: ");
    scanf("%d", &capacity);

    if (passengers < capacity) {
        printf("Total passengers can't be less than car capacity.\n");
        return 0;
    }
    mainSem = dispatch_semaphore_create(capacity-1);

    passengers_to_board = passengers - (passengers % capacity);
    iterations = passengers_to_board/capacity;

    pthread_t passenger_threads[passengers];
    pthread_t car_thread;

    pthread_create(&car_thread, NULL, car, NULL);

    for (int i = 0; i < passengers; ++i) {
        int* passenger_id = malloc(sizeof(int));
        *passenger_id = i;

        pthread_create(&passenger_threads[i], NULL, passenger, (void*)passenger_id);
        dispatch_semaphore_wait(mainSem, DISPATCH_TIME_FOREVER);
    }

    pthread_join(car_thread, NULL);

    for (int i = 0; i < passengers; ++i) {
        pthread_join(passenger_threads[i], NULL);
    }

    return 0;
}
    