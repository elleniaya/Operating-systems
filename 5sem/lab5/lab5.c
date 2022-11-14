#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define ERROR -1
#define STDOUT 1 
#define SUCCESS 0 
#define SECONDS 2
#define COUNT_BYTES_1 16
#define COUNT_BYTES_2 6
#define CALL 1

void cleanup(void* arg){
    write(STDOUT, "\nThread canceled", COUNT_BYTES_1);
}

void* printString(void *args){
    pthread_cleanup_push(cleanup, NULL);
    while (true){
        write(STDOUT, "hello ", COUNT_BYTES_2);
    }
    pthread_cleanup_pop(CALL);
}

int main() {
    pthread_t thread;
    int status = pthread_create(&thread, NULL, printString, NULL);

    if (status){
        printf("Error %d: %s\n", status, strerror(status));
        return ERROR;
    }

    sleep(SECONDS);

    status = pthread_cancel(thread);

    printf("\n");

    if (status){
        printf("Error %d: %s\n", status, strerror(status));
        return ERROR;
    }

    pthread_join(thread, NULL);

    return SUCCESS;
}
