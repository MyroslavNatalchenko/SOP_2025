
# Obsługa sygnałów w języku C — Zadania

## Zadanie 1

**Treść zadania:**  
Obsługę sygnałów możemy bez problemu przerejestrować. Napisz program, który przy pierwszym wywołaniu SIGINT wejdzie do funkcji, jak w przykładzie z zajęć, ale przy następnym wywołaniu już wywoła SIG_DFL.

**Rozwiązanie:**
```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signum);

int main(){
    signal(SIGINT, sig_handler);
    while(1){
        printf("Jestem w mainie!\n");
        sleep(1);
    }
    return 0;
}

void sig_handler(int signum){
    printf("jestem w handlerze!\n");
    signal(SIGINT, SIG_DFL);
}
```

---

## Zadanie 2

**Treść zadania:**  
Napisz programik, który po otrzymaniu od użytkownika jakiegoś inputu o długości 5 (np. stringa ‘jajco’) wyśle sygnał USR1 do handlera, który zapisze go do pliku. W przeciwnym wypadku główna funkcja zapisze input do innego pliku.

**Rozwiązanie:**
```c
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

char input_buffer[100];

void sig_handler(int signum);

int main() {
    signal(SIGUSR1, sig_handler);

    fgets(input_buffer, sizeof(input_buffer), stdin);
    input_buffer[strcspn(input_buffer, "\n")] = '\0';

    if (strlen(input_buffer) == 5) {
        raise(SIGUSR1);
    } else {
        FILE *f = fopen("zad2_other.txt", "a");
        if (f) {
            fprintf(f, "%s\n", input_buffer);
            fclose(f);
        }
    }
    return 0;
}

void sig_handler(int signum) {
    FILE *f = fopen("zad2_five.txt", "a");
    if (f) {
        fprintf(f, "%s\n", input_buffer);
        fclose(f);
    }
}
```

---

## Zadanie 3

**Treść zadania:**  
Napisz program, który zlicza, ile razy otrzymał sygnał SIGINT, a następnie wypisuje tę wartość na ekranie po otrzymaniu sygnału SIGTERM.

**Rozwiązanie:**
```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int cnt = 0;  

void sig_handler(int signum);

int main() {
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    while (1) {
        pause();  
    }
    return 0;
}

void sig_handler(int signum){
    if (signum == SIGINT) {
        cnt++;
        printf("+1");
    }
    if (signum == SIGTERM) {
        printf("Have gotten %d signals with type SIGINT\n", cnt);
    }
}
```

Wyłować signal SIGTERM można za pomocą:
```bash
ps aux | grep a.out
kill -SIGTERM <PID>
```

---

## Zadanie 4

**Treść zadania:**  
Napisz programik, który będzie się wykonywał w pętli, a w momencie otrzymania SIGUSR1 wydrukuje na terminalu potwierdzenie i zabije się.

**Rozwiązanie: (ZROBIŁEM tak żeby samodzielnie po 10 sekundach wyłowywał siganl SIGUSR1 dla łatwiejszego testowania)**
```c
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int signum);

int main() {
    int cnt=0;
    signal(SIGUSR1, sig_handler);

    while (1) {
        cnt++;
        printf("%d \n",cnt);
        if (cnt==10){
            raise(SIGUSR1);
        }
        sleep(1);
    }
    return 0;
}

void sig_handler(int signum) {
    exit(0);
}
```

---

## Zadanie 5

**Treść zadania:**  
Tu użyjemy wiadomości z kilku wcześniejszych zajęć. Napisz program, który się sforkuje, a następnie rodzic zabije dziecko. Przyda się polecenie kill() – w nim możemy podać konkretny PID, który chcemy ubić.

**Rozwiązanie:**
```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sig_handler(int signum);

int main() {
    signal(SIGTERM, sig_handler);
    
    pid_t pid = fork();

    if (pid == 0) {
        printf("Kid. PID: %d\n", getppid());
    } else {
        printf("Parent killed kid. PID: %d\n", getpid());
        kill(pid, SIGTERM);
    }
    return 0;
}

void sig_handler(int signum) {
    printf("SIGTERM signal was created afteer kill\n");
}
```
