#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define COMMON 0
#define PARENT 1
#define CHILD 2

#define SUCCESS 0

#define COUNT_MUTEX 3
#define COUNT_LINE 10

pthread_t thread;

pthread_mutex_t mutexes[COUNT_MUTEX];

void destroyMutexes() {
    for (int i = 0; i < COUNT_MUTEX; i++) {
        pthread_mutex_destroy(&mutexes[i]);
    }
}

void lockMutex(int mutexID) {
    pthread_mutex_lock(&mutexes[mutexID]);
}

void unlockMutex(int mutexID) {
    pthread_mutex_unlock(&mutexes[mutexID]);
}


void joinChildThread() {
    int status = pthread_join(thread, NULL);
    if (status != SUCCESS) {
        printf("Error couldn't join thread = %d\n", status);
        pthread_exit(NULL);
    }
}

void* childPrintStrings() {
	lockMutex(CHILD);
    for (int i = 1; i <= COUNT_LINE; i++) {
        lockMutex(PARENT);
        printf("child thread №%d\n", i);
        unlockMutex(CHILD);
        lockMutex(COMMON);
        unlockMutex(PARENT);
        lockMutex(CHILD);
        unlockMutex(COMMON);
    }
    unlockMutex(CHILD);
}

void startChildThread() {
    int status = pthread_create(&thread, NULL, childPrintStrings, NULL);
    if (status != SUCCESS) {
        printf("Error couldn't create thread = %d\n", status);
        pthread_exit(NULL);
    }
}

void parentPrintStrings() {
	sleep(1);
  for (int i = 1; i <= COUNT_LINE; i++) {
        printf("parent thread №%d\n", i);
        lockMutex(COMMON);
        unlockMutex(PARENT);
        lockMutex(CHILD);
        unlockMutex(COMMON);
        lockMutex(PARENT);
        unlockMutex(CHILD);
    }
    unlockMutex(PARENT);
}

int main() {
    pthread_mutexattr_t attr;
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    for (int i = 0; i < COUNT_MUTEX; i++) {
        pthread_mutex_init(&mutexes[i], &attr);
    }

    lockMutex(PARENT);
    startChildThread();
    parentPrintStrings();
    joinChildThread();
    destroyMutexes();
    return SUCCESS;
}
