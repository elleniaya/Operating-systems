#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define ERROR -1
#define NUMBER 5

pthread_mutex_t mutex1, mutex2, start_mutex;

void* thread_func(void* param){
    pthread_mutex_lock(&start_mutex);
    for (int i = 0; i < NUMBER; i++) {
      pthread_mutex_lock(&mutex2);
      printf("Thread - %d\n", i);
      pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    pthread_mutex_init(&start_mutex, NULL);
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_mutex_lock(&start_mutex);
    
    int res = pthread_create(&tid, NULL, thread_func, NULL);
    if (res){
        printf("Error %d: %s\n", res, strerror(res));
        return ERROR;
    }
    pthread_mutex_lock(&mutex2);
    pthread_mutex_unlock(&start_mutex);
    for (int i = 0; i < NUMBER; i++){
        pthread_mutex_lock(&mutex1);
        printf("Main thread - %d\n", i);
        pthread_mutex_unlock(&mutex2);
    }
  
    pthread_exit(NULL);
}
