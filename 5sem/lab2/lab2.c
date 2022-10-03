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
    pthread_t tid;

    int res = pthread_create(&tid, NULL, thread_func, NULL);
    if (res){
        printf("Error %d: %s\n", res, strerror(res));
        return ERROR;
    }

    int res_join = pthread_join(tid, NULL);
    if (res_join) {
        printf("Error %d: %s\n", res_join, strerror(res_join));
        return ERROR;
    }

    printf("one\n");
    printf("two\n");
    printf("three\n");
    printf("four\n");
    printf("five\n");

    return 0;
}
