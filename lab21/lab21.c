#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define BELL "\a"
#define ERROR 1

int count = 0;
int flag = 1;

void catch_signal(int sig){
    if(sig == SIGQUIT){
        flag = 0;
        return;
    }
    count++;
    printf("%c", BELL);
}

int main(){
        void* res = sigset(SIGINT, catch_signal);
        if(res == SIG_ERR){
                perror("sigset error");
                return ERROR;
        }
        res = sigset(SIGQUIT, catch_signal);
        if(res == SIG_ERR){
                perror("sigset error");
                return ERROR;
        }

        while(flag){
                pause();
        }
  
        printf("\nThe signal sounded %d times\n", count);
        return 0;
}
