#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ERROR -1
#define SUCCESS 0

#define SOCKET_ERROR 1
#define BIND_ERROR 2
#define LISTEN_ERROR 3
#define ACCEPT_ERROR 4
#define READ_ERROR 5
#define CLOSE_ERROR 6
#define UNLINK_ERROR 7

#define BACKLOG 1
#define BUFFER_SIZE 256

int message_read(int client_socket_descriptor) {
  char message[BUFFER_SIZE];
  while(1){
        int read_result = read(client_socket_descriptor, message, BUFFER_SIZE);
        if (read_result == ERROR){
            perror("read error");
            return ERROR;
        }
    
        if (read_result == 0) break;
        for (int i = 0; i < read_result; i++){
            message[i] = toupper(message[i]);
            printf("%c", message[i]);
        }
    }
    return SUCCESS;
}

int main() {
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
  
    int bind_result = bind(socket_descriptor, (const struct sockaddr *) address, sizeof(*address));
    if (bind_result == ERROR) {
        perror("bind error");
        return BIND_ERROR;
    }

    int listen_result = listen(socket_descriptor, BACKLOG);
    if (listen_result == ERROR){
        perror("listen error");
        return LISTEN_ERROR;
    }

    int client_socket_descriptor = accept(socket_descriptor, NULL, NULL);
    if (client_socket_descriptor == ERROR) {
        perror("accept error");
        return ACCEPT_ERROR;
    }
    
    int read_result = message_read(client_socket_descriptor);
  
    int close_result = 0;
    if (read_result == ERROR) {
        close_result = close(client_socket_descriptor);
        if (close_result == ERROR){
              perror("close error");
              return CLOSE_ERROR;
        }
        close_result = close(socket_descriptor);
        if (close_result == ERROR){
              perror("close error");
              return CLOSE_ERROR;
        }
        return READ_ERROR;
    }
  
    close_result = close(client_socket_descriptor);
    if (close_result == ERROR){
              perror("close error");
              return CLOSE_ERROR;
    }
  
    int unlink_result = unlink(ADDR);
    if (unlink_result == ERROR){
        perror("unlink error");
        return UNLINK_ERROR;
    }
  
    return SUCCESS;
}
