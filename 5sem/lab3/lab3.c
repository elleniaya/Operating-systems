#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1

void *printString(void *args) {
    for (char **s = (char **)args; *s != NULL; ++s) {
        printf("%s\n", *s);
    }
}

int main() {
   pthread_t threads[4];
   char *args[][4] = {
            {"1 thread:: 1 line", "1 thread:: 2 line", "1 thread:: 3 line", NULL},
            {"2 thread:: 1 line", "2 thread:: 2 line", "2 thread:: 3 line", NULL},
            {"3 thread:: 1 line", "3 thread:: 2 line", "3 thread:: 3 line", NULL},
            {"4 thread:: 1 line", "4 thread:: 2 line", "4 thread:: 3 line", NULL}
   };

   int status = 0;

   for (int i = 0; i < 4; i++){
       status = pthread_create(&threads[i], NULL, printString, (void*)args[i]);

       if (status){
        printf("Error %d: %s\n", status, strerror(status));
        return ERROR;
       }
   }

    for (int i = 0; i < 4; i++){
        status = pthread_join(threads[i], NULL);

        if (status){
          printf("Error %d: %s\n", status, strerror(status));
          return ERROR;
         }
    }

    return 0;
}
