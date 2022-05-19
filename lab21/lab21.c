#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define SOUND "\a"
#define ERROR 1

int count = 0;
bool flag = true;

void catch_signal(int sig){
    if(sig == SIGQUIT){
        flag = false;
        return;
    }
    count++;
    printf("%c", SOUND);
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
