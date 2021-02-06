#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

void * task_1(void * arg)
{
    printf("Thread id of thread 1: %lu\n", pthread_self());
}

void * task_2(void * arg)
{
    printf("Thread id of thread 2: %lu\n", pthread_self());
}

void * task_3(void * arg)
{
    printf("Thread id of thread 3: %lu\n", pthread_self());
}

int main(int argc, char * argv[])
{
    pthread_t tid_1, tid_2, tid_3;

    if(pthread_create(&tid_1, NULL, task_1, NULL) != 0)
        ERR_EXIT("pthread_create() 1");
    if(pthread_create(&tid_2, NULL, task_2, NULL) != 0)
        ERR_EXIT("pthread_create() 2");
    if(pthread_create(&tid_3, NULL, task_3, NULL) != 0)
        ERR_EXIT("pthread_create() 3");

    if(pthread_join(tid_1, NULL) != 0)
        ERR_EXIT("pthread_join() 1");
    if(pthread_join(tid_2, NULL) != 0)
        ERR_EXIT("pthread_join() 2");
    if(pthread_join(tid_3, NULL) != 0)
        ERR_EXIT("pthread_join() 3");
    pthread_exit(NULL);
    exit(EXIT_SUCCESS);
}