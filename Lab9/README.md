1: 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // dla usleep

void *thread_function(void *arg) {
    while (1) {
        printf("Jestem wątkiem\n");
        usleep(500000); // 500 ms
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);

    while (1) {
        printf("Jestem mainem\n");
        usleep(2500000); // 2500 ms
    }

    return 0;
}

2:
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    for (int i = 0; i < 10; i++) {
        printf("Wątek: %d\n", i);
        usleep(100000); // 100 ms
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);

    for (int i = 0; i < 10; i++) {
        printf("Main: %d\n", i);
        usleep(150000); // 150 ms
    }

    pthread_join(thread, NULL);
    printf("Zakończono działanie programu.\n");

    return 0;
}

3:
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int counting = 0;
int counter = 0;
pthread_t timer_thread;

void *timer_function(void *arg) {
    while (1) {
        if (counting) {
            counter++;
            printf("Czas: %d sekund\n", counter);
        }
        sleep(1);
    }
    return NULL;
}

int main() {
    char command[20];

    pthread_create(&timer_thread, NULL, timer_function, NULL);

    while (1) {
        printf("Podaj komendę (start/stop/reset/exit): ");
        scanf("%s", command);

        if (strcmp(command, "start") == 0) {
            counting = 1;
        } else if (strcmp(command, "stop") == 0) {
            counting = 0;
        } else if (strcmp(command, "reset") == 0) {
            counter = 0;
            printf("Zresetowano licznik.\n");
        } else if (strcmp(command, "exit") == 0) {
            printf("Kończenie programu.\n");
            exit(0);
        } else {
            printf("Nieznana komenda.\n");
        }
    }

    return 0;
}
