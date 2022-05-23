#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>
#include <time.h>

#define ERROR -1
#define ERROR_P2OPEN 1
#define FCLOSE_ERROR 2
#define P2CLOSE_ERROR 3

int main() {
    FILE *fp[2];

    int p2o = p2open("sort -n", fp);
    if (p2o == ERROR) { 
        perror("p2open error");
        return ERROR_P2OPEN; 
    }

    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        fprintf(fp[0], "%d\n", rand() % 100);
    }

    int close = fclose(fp[0]);
    if (close == ERROR) {
        perror("fclose error");
        return FCLOSE_ERROR;  
    }

    char c;
    int count = 0;
    while (read(fileno(fp[1]), &c, 1) == 1) {
        if (c == '\n') {
            printf(++count % 10 == 0 ? "\n" : " ");
            continue;
        }

        printf("%c", c);
    }
    
    int p2c = p2close(fp);
    if (p2c == ERROR) {
        perror("p2close error");
        return P2CLOSE_ERROR;
    }

    return 0;
}
