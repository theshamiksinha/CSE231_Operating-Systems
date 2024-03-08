// At most 2 philosophers can eat , that too with the condition that those 2 philosophers should be 
// having unique Forks to choose , like at a time (Philosopher0 and Philosopher2) can eat but
// Philosopher0 and Philosophers1 cannot eat at the same time because they would be sharing Fork1

// In order to make the code deadlock free, I have used Odd-Even rule , where philosophers having even
// id like (0,2,4) choose left Fork first then right Fork and converse for philosophers having
// even id.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t Fork[NUM_PHILOSOPHERS];
pthread_cond_t can_eat[NUM_PHILOSOPHERS];

void thinking(int philosopher_id){
    printf("Philosopher %d is thinking.\n", philosopher_id);
    sleep(1);
}

void eating(int philosopher_id){
    printf("Philosopher %d is eating.\n", philosopher_id);
    sleep(1);
}

void *philosopher(void *arg) {
    int philosopher_id = *(int *)arg;
    int left_Fork = philosopher_id;
    int right_Fork = (philosopher_id + 1) % (NUM_PHILOSOPHERS);

    while (1) {
        // Think
        thinking(philosopher_id);

        // Philosopher picking Forks
        if(philosopher_id % 2 == 0){
            //doing this to avoid deadlock , philosopher id's which are even are made to pick left 
            //stick first then right stick
            pthread_mutex_lock(&Fork[left_Fork]);
            printf("Philosopher %d picked up left Fork %d.\n", philosopher_id, left_Fork);
            pthread_mutex_lock(&Fork[right_Fork]);
            printf("Philosopher %d picked up right Fork %d.\n", philosopher_id, right_Fork);
        }
        else{
            //doing this to avoid deadlock , philosopher id's which are odd are made to pick right 
            //stick first then left stick
            pthread_mutex_lock(&Fork[right_Fork]);
            printf("Philosopher %d picked up right Fork %d.\n", philosopher_id, right_Fork);
            pthread_mutex_lock(&Fork[left_Fork]);
            printf("Philosopher %d picked up left Fork %d.\n", philosopher_id, left_Fork);
        }

        // Eat
        eating(philosopher_id);

        // Put down Forks
        if(philosopher_id % 2 != 0){
            pthread_mutex_unlock(&Fork[left_Fork]);
            printf("Philosopher %d put down left Fork %d.\n", philosopher_id, left_Fork);
            pthread_mutex_unlock(&Fork[right_Fork]);
            printf("Philosopher %d put down right Fork %d.\n", philosopher_id, right_Fork);
        }
        else{
            pthread_mutex_unlock(&Fork[right_Fork]);
            printf("Philosopher %d put down right Fork %d.\n", philosopher_id, right_Fork);
            pthread_mutex_unlock(&Fork[left_Fork]);
            printf("Philosopher %d put down left Fork %d.\n", philosopher_id, left_Fork);
        }

        //This is going to signal those philosophers who are blocked and want this particular fork
        pthread_cond_signal(&can_eat[left_Fork]);
        pthread_cond_signal(&can_eat[right_Fork]);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutex locks for each Fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&Fork[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for philosopher threads to finish (this will never happen in this example)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}



