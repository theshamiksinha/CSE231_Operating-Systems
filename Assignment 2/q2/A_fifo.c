#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <fcntl.h>
#include <time.h>


int main() {
    pid_t pid;
    int status;
    struct timespec start_time, end_time;
    double process_time;

    pid = fork();

    if (pid == -1) {
    perror("fork");
    exit(1);
    }
    
    else if (pid == 0) {

        

        char *program_name = "./count1";
        
        struct sched_param param;
        param.sched_priority = 1; 
        sched_setscheduler(getpid(), SCHED_FIFO, &param);

        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        if (sched_setaffinity(0, sizeof(cpuset), &cpuset) == -1) {
            perror("sched_setaffinity");
            exit(1);
        }

        execl(program_name, program_name, NULL);
        perror("execl");
        exit(1);
    }

    if (clock_gettime(CLOCK_MONOTONIC, &start_time) == -1) {
        perror("clock_gettime");
        return 1;
    }

    waitpid(pid, &status, 0);

    if (clock_gettime(CLOCK_MONOTONIC, &end_time) == -1) {
        perror("clock_gettime");
        return 1;
    }

    process_time = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_nsec - start_time.tv_nsec) / 1e9;


    FILE *file;
    file = fopen("data.txt", "a");

    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    fprintf(file,"f ");

    fprintf(file, "%lf\n", process_time);

    fclose(file);

    printf("Process 1 (fifo) execution time: %lf seconds\n", process_time);

    return 0;
}
