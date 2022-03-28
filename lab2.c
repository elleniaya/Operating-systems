#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ERROR -1
#define PUTENV_ERROR -2
#define TIME_ERROR -3
#define CTIME_ERROR -4
#define LOCALTIME_ERROR -5

extern char *tzname[];

int main() {
    time_t now; //определяем переменную now типа time_t
    struct tm *tm; //определяем указатель на структуру tm
    //Изменяем переменную среды TZ
    //Наиболее употребительный формат значения TZ, применяемый в современных Unix-системах — это имя файла в каталоге /usr/share/lib/zoneinfo/
    int Putenv_Res = putenv ("TZ=America/Los_Angeles"); 
    //Обработка ошибки
    if (Putenv_Res == ERROR) {
        perror("error putenv");
        return PUTENV_ERROR;
    }

    time_t Rtime =  time(&now);
    //Обработка ошибки
    if (Rtime == ERROR) {
        perror("error time");
        return TIME_ERROR;
    }

    char *STRTime = ctime(&now);
    //Обработка ошибки
    if (STRTime == NULL) {
         perror("error ctime");
         return CTIME_ERROR;
    }
    
    printf("%s", STRTime);

    tm = localtime(&now);
    //Обработка ошибки
    if (tm == NULL) {
         perror("error localtime");
         return LOCALTIME_ERROR;
    }
    //печать значений полей структуры tm
    printf("%d/%d/%02d %d:%02d %s\n",
         tm->tm_mon + 1, tm->tm_mday,
         tm->tm_year + 1900, tm->tm_hour,
         tm->tm_min, tzname[tm->tm_isdst]);

   exit(0);
}
