#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>
#include <time.h>

#define ERROR 1
#define CLOSING_ERROR 2

int main() {
    FILE *fp[2];

    int p2o = p2open("sort -n", fp);
    if (p2o == -1) { 
        perror("p2open error");
        return ERROR; 
    }

    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        fprintf(fp[0], "%d\n", rand() % 100);
    }

    int close = fclose(fp[0]);
    if (close == EOF) {
        perror("fclose error");
        return CLOSING_ERROR;  
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
    if (p2c == -1) {
        perror("p2close error");
        return CLOSING_ERROR;
    }

    return 0;
}
