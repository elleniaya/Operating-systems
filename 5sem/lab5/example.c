#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define ERROR -1

void cleanup(void* arg){
    free((int*)arg);
}

void* printString(void *args){
    int* x = (int*)malloc(123*sizeof(int));
    pthread_cleanup_push(cleanup, x);
    for (int i = 0; i < 123; i++){
            x[i] = i;
    }
    sleep(20);
    pthread_cleanup_pop(0);
}

int main() {
    pthread_t thread;
    int status = pthread_create(&thread, NULL, printString, NULL);

    if (status){
        printf("Error 1 %d: %s\n", status, strerror(status));
        return ERROR;
    }

    sleep(2);

    status = pthread_cancel(thread);

    printf("\n");

    if (status){
        printf("Error 2 %d: %s\n", status, strerror(status));
        return ERROR;
    }

    pthread_join(thread, NULL);

    return 0;
}
