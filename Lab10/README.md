# Zadanie 1

## Ustawienie
Napisz program w języku C, który tworzy 5 wątków. Każdy wątek ma zwiększyć wspólną zmienną globalną o 1, 1000 razy. Wykorzystaj mutex, aby zapewnić, że dostęp do zmiennej jest zsynchronizowany i żaden wątek nie zmodyfikuje jej w tym samym czasie co inny wątek.

## Rozwiązanie
```c
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5
#define INCREMENTS 1000

int counter = 0;
pthread_mutex_t mutex;

void* increment_counter(void* arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Finalna wartość licznika: %d (oczekiwane: %d)\n", counter, NUM_THREADS * INCREMENTS);
    return 0;
}
```

# Zadanie 2

## Ustawienie
Napisz program, który symuluje problem producenta-konsumenta z jednym producentem i jednym konsumentem, korzystając z semaforów. Producent ma wypełniać bufor danymi (np. liczby całkowite), a konsument ma te dane pobierać i wyświetlać. Użyj semaforów do synchronizacji dostępu do bufora.

## Rozwiązanie
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define PRODUCE_COUNT 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t sem_empty;
sem_t sem_full;
pthread_mutex_t mutex;

void* producer_function(void* arg) {
    for (int i = 0; i < PRODUCE_COUNT; i++) {
        int item = rand() % 100;

        sem_wait(&sem_empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("PROD: ADD %d TO %d\n", item, in);
        in = (in + 1)%BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); 
        sem_post(&sem_full);

        sleep(1);
    }

    pthread_exit(NULL);
}

void* consumer_function(void* arg) {
    for (int i = 0; i < PRODUCE_COUNT; i++) {
        sem_wait(&sem_full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("KONS: TAKE %d FROM %d\n", item, out);
        out = (out + 1)%BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  
        sem_post(&sem_empty);

        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    if (sem_init(&sem_empty, 0, BUFFER_SIZE) == -1 ||
        sem_init(&sem_full, 0, 0) == -1) {
        perror("Nie udało się zainicjować semaforów");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&producer_thread, NULL, producer_function, NULL) != 0) {
        perror("Błąd przy tworzeniu wątku producenta");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&consumer_thread, NULL, consumer_function, NULL) != 0) {
        perror("Błąd przy tworzeniu wątku konsumenta");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(producer_thread, NULL) != 0) {
        perror("Błąd przy oczekiwaniu na zakończenie producenta");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(consumer_thread, NULL) != 0) {
        perror("Błąd przy oczekiwaniu na zakończenie konsumenta");
        exit(EXIT_FAILURE);
    }

    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
```

# Zadanie 3

## Ustawienie
Napisz program w języku C, który symuluje problem czytelników i pisarzy. Użyj semaforów do synchronizacji, aby wielu czytelników mogło jednocześnie czytać, ale tylko jeden pisarz mógł pisać w danym momencie. Gdy pisarz pisze, żaden czytelnik nie może czytać.

## Rozwiązanie
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_READERS 3
#define NUM_WRITERS 1

int shared_data = 0;
int reader_count = 0;

sem_t resource_access;
sem_t reader_count_mutex;

void* reader_function(void* arg) {
    int *id = (int *) arg;

    while (1) {
        sem_wait(&reader_count_mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&resource_access);
        }
        sem_post(&reader_count_mutex);

        printf("Czytelnik %d: czyta dane = %d\n", *id, shared_data);
        sleep(1);

        sem_wait(&reader_count_mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&resource_access);
        }
        sem_post(&reader_count_mutex);

        sleep(2); 
    }

    pthread_exit(NULL);
}

void* writer_function(void* arg) {
    int *id = (int *) arg;

    while (1) {
        sem_wait(&resource_access);

        shared_data += 10;
        printf("Pisarz %d: pisze dane = %d\n", *id, shared_data);
        sleep(2);

        sem_post(&resource_access);

        sleep(3);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    if (sem_init(&resource_access, 0, 1) == -1 ||
        sem_init(&reader_count_mutex, 0, 1) == -1) {
        perror("Nie udało się zainicjować semaforów");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        if (pthread_create(&readers[i], NULL, reader_function, &reader_ids[i]) != 0) {
            perror("Błąd przy tworzeniu wątku czytelnika");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        if (pthread_create(&writers[i], NULL, writer_function, &writer_ids[i]) != 0) {
            perror("Błąd przy tworzeniu wątku pisarza");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&resource_access);
    sem_destroy(&reader_count_mutex);

    return 0;
}
```
