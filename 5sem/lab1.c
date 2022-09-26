#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define ERROR -1

void* thread_func(void* param){
    printf("six\n");
    printf("seven\n");
    printf("eight\n");
    printf("nine\n");
    printf("ten\n");
}

int main() {
    pthread_t thread;

    int res = pthread_create(&thread, NULL, thread_func, NULL);
    if (res){
        printf("Error %d: %s\n", res, strerror(res));
        return ERROR;
    }

    printf("one\n");
    printf("two\n");
    printf("three\n");
    printf("four\n");
    printf("five\n");

    pthread_exit(NULL);

    return 0;
}
