#include <stdio.h>
#include <unistd.h>

#define FORK_ERROR -1
#define ERROR 1
#define CHILD 0

int main() {
  pid_t pid = fork();
  if (pid == FORK_ERROR) {
        perror("fork error");
        return ERROR;
  }
  
  if (pid == CHILD) {
        execlp("cat", "cat", "text.txt", NULL);
        perror("execlp error");
        return ERROR;
  }
  
  printf("This is the parent process\n");
  return 0;
}
