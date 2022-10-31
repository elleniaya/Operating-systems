#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define ERROR -1

void cleanup(void* arg){
    write(1, "\nThread canceled", 16);
}

void* printString(void *args){
    pthread_cleanup_push(cleanup, NULL);
    while (true){
        write(1, "hello ", 6);
    }
    pthread_cleanup_pop(1);
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

    pthread_join(thread, NULL);

    return 0;
}
