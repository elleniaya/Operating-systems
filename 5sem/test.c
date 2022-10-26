#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define ERROR -1

void* printString(void *args){
      while (true){
             printf("hello ");
      }
}

void catch_signal(int sig){
       if (sig == SIGINT) {
              pthread_exit(NULL);
       }
}

int main() {
     void* res = sigset(SIGINT, catch_signal);
     pthread_t thread;
     int status = pthread_create(&thread, NULL, printString, NULL);

     if (status){
         printf("Error %d: %s\n", status, strerror(status));
         return ERROR;
     }   
  
     sleep(2);

     int res = pthread_kill(thread, SIGINT);
     return 0;
}
