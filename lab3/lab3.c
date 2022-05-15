#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define SUCCESS 0
#define OPENING_ERROR 1
#define CLOSING_ERROR 2
#define ERROR_SETUID 3
#define ERROR -1

int open_file(){
    FILE* file = fopen("file", "r");
    if (file == NULL){
        perror("error opening file");
        return OPENING_ERROR;
    } 
    printf("File opened\n");
    int close = fclose(file);
    if (close == EOF) return CLOSING_ERROR;  
    return SUCCESS;
}

void print_ID(){
    printf("Real ID = %d\n", getuid()); //Печатаем реальный идентификатор пользователя
    printf("Effective ID = %d\n", geteuid()); //Печатаем эффективный идентификатор пользователя
}

int main(){
    print_ID();

    int res_open_file = open_file();  
  
    int res_setuid = setuid(getuid()); //Установка эффективого индентификатора равным действительному
    if (res_setuid == ERROR){ 
        perror("error setuid");
        return ERROR_SETUID;
    }
    
    print_ID();
    res_open_file = open_file(); 
    return res_open_file;
}
