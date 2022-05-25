#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>
#include <time.h>

#define ERROR -1
#define ERROR_P2OPEN 1
#define FCLOSE_ERROR 2
#define P2CLOSE_ERROR 3
#define COUNT_NUMBER 100
#define RANGE 100

void generate_list(FILE *fp[2]) {
    srand(time(NULL));
    for (int i = 0; i < COUNT_NUMBER; i++) {
        fprintf(fp[0], "%d\n", rand() % RANGE);
    }
}

void print_list(FILE *fp[2]) {
    char c;
    int count = 0;
    int result = 0;
    int n = 0;
    while(1) {
        result = read(fileno(fp[1]), &c, 1);
        if (result == 1) {
            if (c == '\n') {
                if (n == 1) printf(" ");
                n = 0;
                printf(++count % 10 == 0 ? "\n" : "  ");
                continue;
            }
            n++;
            printf("%c", c);
        } else break;
    }
}

int main() {
    FILE *fp[2];

    int p2o = p2open("sort -n", fp);
    if (p2o == ERROR) {
        perror("p2open error");
        return ERROR_P2OPEN;
    }

    generate_list(fp);

    int close = fclose(fp[0]);
    if (close == ERROR) {
        perror("fclose error");
        return FCLOSE_ERROR;
    }

    print_list(fp);

    int p2c = p2close(fp);
    if (p2c == ERROR) {
        perror("p2close error");
        return P2CLOSE_ERROR;
    }
    return 0;
}
