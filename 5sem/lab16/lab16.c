#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

sem_t* sem0,* sem1;

void* child_thread(){
    for(int i = 0; i < 10; ++i){
        sem_wait(sem1);  // На всех итерациях "потомок" заблокирован и ожидает, пока "родитель" не напечатает текст
                         // и не инкрементирует sem1 у "потомка".
        printf("%d child thread text!\n", i);
        sem_post(sem0);  // Пускаем "родителя" на новую итерацию цикла печати текста + инкрементирования sem0
    }
}
int main() {
    if((sem0 = sem_open("/sem0", O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED){ // Создаем именованный семафор с маской прав доступа:
                                                                                 // процесс имеет право на чтение и запись информации в файл
        perror("sem_open failed");
        exit(1);
    }
    if((sem1 = sem_open("/sem1", O_CREAT, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED){
        perror("sem_open failed");
        exit(1);
    }


    pid_t fork_retval; // то же самое, что pthread_t, только здесь это тип данных для ID процесса
    if((fork_retval = fork()) == -1){ //создаем процесс
        perror("fork failed");
    }
    else if(fork_retval == 0){ // Созданный процесс попадает сюда
        child_thread();
    }
    else {
        for (int i = 0; i < 10; ++i) {
            sem_wait(sem0); // Блокируем "родителя". Но на 1 итерации цикла идем "родителем" дальше.
                            // На 2 и больше итерациях "родитель" ждет, пока "потомок" не напечатает текст
                            // и не инкерментирует sem0 у "родителя"
            printf("%d master thread text!\n", i);
            sem_post(sem1); // Пускаем "потомка" на новую итерацию цикла печати текста + инкрементирования sem1
        }
        wait(0);
    }

    sem_close(sem0);
    sem_close(sem1);


    exit(0);
}
