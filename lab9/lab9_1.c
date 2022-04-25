#include <stdio.h>
#include <unistd.h>

#define FORK_ERROR -1
#define ERROR 1
#define CHILD 0
#define EXECLP_ERROR -1

int main(int argc, char** argv) {
  pid_t pid = fork();
  if (pid == FORK_ERROR) {
        perror("fork error");
        return ERROR;
  }
  
  if (pid == CHILD) {
        execlp("cat", "cat", argv[1], NULL);
        perror("execlp error");
        return EXECLP_ERROR;
  }
  
  printf("This is the parent process\n");
  return 0;
}
