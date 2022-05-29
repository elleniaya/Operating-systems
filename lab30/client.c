#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define ERROR -1

#define SOCKET_ERROR 1
#define CONNECT_ERROR 2
#define CLOSE_ERROR 3
#define SIGSET_ERROR 4

#define BUFFER_SIZE 256

void catch_signal(int sig) {
    printf("server is not available");
}

int message_write(int socket_descriptor) {
    char message[BUFFER_SIZE];
    while(TRUE){
        int read_result = read(STDIN_FILENO, message, BUFFER_SIZE);
        if (read_result == ERROR){
            perror("read error");
            return ERROR;
        }
        if (read_result == 0) break;
        int write_result = write(socket_descriptor, message, read_result);
        if (write_result == ERROR){
            perror("write error");
            return ERROR;
        }
    }
    return SUCCESS;
}

int main() {
    void* sigset_res = sigset(SIGPIPE, catch_signal);
    if (sigset_res == SIG_ERR){
        perror("sigset error");
        return SIGSET_ERROR;
    }
    
    char ADDR[] = "mysocket";
  
    struct sockaddr_un address;
    memset(&address, 0, sizeof(struct sockaddr_un));
  
    int socket_descriptor = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_descriptor == ERROR) {
        perror("socket error");
        return SOCKET_ERROR;
    }
  
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, ADDR);
    
    int close_result = 0;
    int connect_res = connect(socket_descriptor, (struct sockaddr*) &address, sizeof(address));
    if (connect_res == ERROR) {
        perror("connect error");
        close_result = close(socket_descriptor);
        if (close_result == ERROR){
             perror("close error");
             return CLOSE_ERROR;
        }
        return CONNECT_ERROR;
    }
    
    int write_res = write_message(socket_descriptor);
    if (write_res == ERROR){
        close_result = close(socket_descriptor);
        if (close_result == ERROR){
             perror("close error");
             return CLOSE_ERROR;
        }
        return ERROR;
    }
    
    close_result = close(socket_descriptor);
    if (close_result == ERROR){
         perror("close error");
         return CLOSE_ERROR;
    }
    return SUCCESS;
}
