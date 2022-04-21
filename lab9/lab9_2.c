#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define FORK_ERROR -1
#define ERROR 1
#define CHILD 0
#define EXECLP_ERROR -1
#define WAIT_ERROR -1

int main() {
  pid_t pid = fork();
  if (pid == FORK_ERROR) {
        perror("fork error");
        return ERROR;
  }
  
  if (pid == CHILD) {
        execlp("cat", "cat", "text.txt", NULL);
        perror("execlp error");
        return EXECLP_ERROR;
  }
  
  pid_t wait_res = wait(NULL);
  if (wait_res == WAIT_ERROR) {
        perror("wait error");
        return WAIT_ERROR;
  }
  
  printf("This is the parent process\n");
  return 0;
}
