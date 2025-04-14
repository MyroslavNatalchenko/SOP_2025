# Zadanie 1:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t children[3];
    int status;

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Proces potomny %d: PID = %d, Parent PID = %d\n", i + 1, getpid(), getppid());
            exit(i + 1); 
        } else if (pid > 0) {
            children[i] = pid; 
        } 
    }

    for (int i = 0; i < 3; i++) {
        pid_t ended_pid = waitpid(children[i], &status, 0);
        if (WIFEXITED(status)) {
            printf("Proces potomny o PID %d zakończył się kodem wyjścia: %d\n", ended_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
```

# Zadanie 2:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Dziecko: PID = %d, PPID = %d.\n", getpid(), getppid());
        sleep(3);
        printf("Dziecko po oczekiwaniu: PPID = %d.\n", getppid());
        exit(0);
    } else if (pid > 0) {
        wait(NULL);
    } 
}
```

# Zadanie 3:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if (pid1 == 0) {
        printf("Jestem procesem 1 (PID = %d)\n", getpid());
        sleep(1);
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("Jestem procesem 2 (PID = %d)\n", getpid());
        sleep(2);
        exit(2);
    }

    for (int i = 0; i < 2; i++) {
        pid_t finished = waitpid(-1, &status, 0); 
        if (WIFEXITED(status)) {
            printf("Proces o PID %d zakończył się jako %d. Kod wyjścia: %d\n", 
                   finished, i + 1, WEXITSTATUS(status));
        }
    }

    return 0;
}
```

# Zadanie 4:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        pid_t grandchild = fork();
        if (grandchild == 0) {
            printf("Wnuk działa z PID rownym %d\n», getpid());
            sleep(2);
            exit(5);
        } else {
            int status;
            pid_t ended = wait(&status);
            printf("Wnuk zakończony z PID = %d, kod = %d\n", ended, WEXITSTATUS(status));
            exit(0);
        }
    } else {
        exit(0);
    }
}
```

# Zadanie 5:
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 == 0) {
        printf("Dziecko 1: PID = %d, PPID = %d\n", getpid(), getppid());

        pid_t wnuk1 = fork();
        if (wnuk1 == 0) {
            printf("Wnuk 1: PID = %d, PPID = %d\n", getpid(), getppid());
            exit(0);
        } else {
            wait(NULL);
            exit(0);
        }
    } else {
        wait(NULL);
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        printf("Dziecko 2: PID = %d, PPID = %d\n", getpid(), getppid());

        pid_t wnuk2 = fork();
        if (wnuk2 == 0) {
            printf("Wnuk 2: PID = %d, PPID = %d\n", getpid(), getppid());
            exit(0);
        } else {
            wait(NULL);
            exit(0); 
        }
    } else {
        wait(NULL);
    }

    return 0;
}
```
