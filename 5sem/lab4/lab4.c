#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define ERROR -1

void* printString(void *args){
    while (true){
        printf("hello ");
    }
}

int main() {
    pthread_t thread;
    int status = pthread_create(&thread, NULL, printString, NULL);

    if (status){
        printf("Error %d: %s\n", status, strerror(status));
        return ERROR;
    }

    sleep(2);

    status = pthread_cancel(thread);

    printf("\n");

    if (status){
        printf("Error %d: %s\n", status, strerror(status));
        return ERROR;
    }

    return 0;
}
