#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

#define value 1000000000L; 

void *countA(void *arg) {

    int* priority = (int*) arg;
    struct sched_param param;
    param.sched_priority = (int)priority[0];
    int z = pthread_setschedparam(pthread_self(), SCHED_OTHER, &param); 

    struct timespec start, stop; 
    if ( clock_gettime( CLOCK_MONOTONIC, &start) == -1) {
        printf("Error occured with clock_gettime");
    }

    long long int x;
    for (x = 1; x <= 4294967295; x++) { 
    }

    printf("A = %lld\n", x);

    if ( clock_gettime( CLOCK_MONOTONIC, &stop) == -1) {
        printf("Error occured with clock_gettime");
    }

    double timeTaken = ( stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec) / (double) value;
    printf("A time = %lf\n", timeTaken);

    FILE *fp;
    fp = fopen("a.txt", "a");
    char buf[1024];
    sprintf(buf, "%lf ", timeTaken);
    fputs(buf, fp);

    return NULL;
}

void *countB(void *arg) {

    int* priority = (int*) arg;
    struct sched_param param, tester;
    param.sched_priority = (int)priority[1];
    int z =pthread_setschedparam(pthread_self(), SCHED_RR, &param); 


    struct timespec start, stop; 
    if ( clock_gettime( CLOCK_MONOTONIC, &start) == -1) {
        printf("Error occured with clock_gettime");
    }

    long long int x;
    for (x = 1; x <= 4294967295; x++) { 
    }

    printf("B = %lld\n", x);
    if ( clock_gettime( CLOCK_MONOTONIC, &stop) == -1) {
        printf("Error occured with clock_gettime");
    }

    double timeTaken = ( stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec) / (double) value;
    printf("B time = %lf\n", timeTaken);

    FILE *fp;
    fp = fopen("b.txt", "a");
    char buf[1024];
    sprintf(buf, "%lf ", timeTaken);
    fputs(buf, fp);

    return NULL;
}

void *countC(void *arg) {

    int* priority = (int*) arg;
    struct sched_param param;
    param.sched_priority = (int)priority[1];
    int z =pthread_setschedparam(pthread_self(), SCHED_FIFO, &param); 


    struct timespec start, stop; 
    if ( clock_gettime( CLOCK_MONOTONIC, &start) == -1) {
        printf("Error occured with clock_gettime");
    }

    long long int x;
    for (x = 1; x <= 4294967295; x++) { 
    }

    printf("C = %lld\n", x);
    if ( clock_gettime( CLOCK_MONOTONIC, &stop) == -1) {
        printf("Error occured with clock_gettime");
    }

    double timeTaken = ( stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec) / (double) value;
    printf("C time = %lf\n", timeTaken);

    FILE *fp;
    fp = fopen("c.txt", "a");
    char buf[1024];
    sprintf(buf, "%lf ", timeTaken);
    fputs(buf, fp);

    return NULL;
}

int main() {

    pthread_t thrA, thrB, thrC;
    int args[2];

    for (int i = 0; i<10; i++) {

        args[0] = 0 + 2*i;
        args[1] = 1 + 10*i;

        pthread_create(&thrA, NULL, &countA, args);
        pthread_create(&thrB, NULL, &countB, args);
        pthread_create(&thrC, NULL, &countC, args);

        pthread_join(thrA, NULL);
        pthread_join(thrB, NULL);
        pthread_join(thrC, NULL);

    } 
}