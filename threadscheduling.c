#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<sys/resource.h>
#include<pthread.h>
#include<string.h>
#include<sched.h>
#include<stdlib.h>
#include<math.h>

pthread_t t1;
pthread_t t2;
pthread_t t3;

struct sched_param p1;
struct sched_param p2;
struct sched_param p3;

void *countA(){
    long k,j;
    struct sched_param param1;
    param1.sched_priority=0;
    struct timespec start, finish;
    pthread_setschedparam(t1,SCHED_OTHER,&param1);
    k=0;
    clock_gettime(CLOCK_REALTIME, &start);
    for(long i= 0 ; i<pow(2,32);i++){
        k++;
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    double time_taken = ((double)(finish.tv_sec - start.tv_sec)) +((double)(finish.tv_nsec - start.tv_nsec)/((double)(1000000000))) ;
    printf("Time Taken : %.2lf", time_taken);
    return NULL;
}

void *countB(){
    long k;
    long j;
    struct sched_param param2;
    param2.sched_priority=100;
    struct timespec start, finish;
    pthread_setschedparam(t2,SCHED_RR,&param2);
    k=0;
    j=pow(2,32);
    clock_gettime(CLOCK_REALTIME, &start);
    for(long i=0;i<j;i++){
        k++;
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    double time_taken = ((double)(finish.tv_sec - start.tv_sec)) +((double)(finish.tv_nsec - start.tv_nsec)/((double)(1000000000))) ;
    printf("Time Taken : %.2lf", time_taken);
    return NULL;
}

void *countC(){
    long k;
    long j;
    struct timespec start, finish;
    struct sched_param param3;
    param3.sched_priority=90;
    pthread_setschedparam(t3,SCHED_FIFO,&param3);
    k=0;
    j=pow(2,23);
    clock_gettime(CLOCK_REALTIME, &start);
    for(long i= 0;i<j;i++){
        k++;
    }
    clock_gettime(CLOCK_REALTIME, &finish);
    double time_taken = ((double)(finish.tv_sec - start.tv_sec)) +((double)(finish.tv_nsec - start.tv_nsec)/((double)(1000000000))) ;
    printf("Time Taken : %.2lf",time_taken);
    return NULL;
}

int main(){
    pthread_create(&t1,NULL,&countA,NULL);
    pthread_create(&t2,NULL,&countB,NULL);
    pthread_create(&t3,NULL,&countC,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    return 0;
}
