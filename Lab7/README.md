## Zad 1

**Treść zadania:**

Napisz program, który odczyta i wydrukuje na terminalu znak po znaku zawartość pliku. Każdy znak powiększ przed drukiem o 1, aby plik tekstowy z ciągiem 10asdf wydrukował ciąg ‘21bteg’

**Rozwiązanie:**

```c
#include <stdio.h>

int main() {
    FILE *text;
    int char_c;

    text = fopen("zad1_input.txt", "r");
    if (text != NULL) {
        while ((char_c = fgetc(text)) != EOF) {
            printf("%c", char_c + 1);
        }
    } else { return 1; }

    fclose(text);
    return 0;
}
```

## Zad 2

**Treść zadania:**

Przerób poprzedni program (polecam go skopiować i pracować na nowoutworzonym) tak, aby zapisywał do nowego pliku to, co w poprzednim programie drukował.

**Rozwiązanie:**

```c
#include <stdio.h>

int main() {
    FILE *text_in, *text_out;
    int char_c;

    text_in = fopen("zad2_input.txt", "r");
    text_out = fopen("zad2_output.txt", "w");

    if (text_in != NULL && text_out != NULL) {
        while ((char_c = fgetc(text_in)) != EOF) {
            fputc(char_c + 1, text_out);
        }
    } else {
        return 1;
    }

    fclose(text_in);
    fclose(text_out);
    return 0;
}
```

## Zad 3

**Treść zadania:**

Napisz program, który zapisze wprowadzony przez użytkownika tekst do pliku tekstowego. Następnie program powinien wczytać zapisany tekst i wyświetlić go na ekranie.

**Rozwiązanie:**

```c
#include <stdio.h>

int main() {
    FILE *text;
    char tekst[1000];

    fgets(tekst, sizeof(tekst), stdin);

    text = fopen("zad3_input.txt", "w");
    if (text != NULL) {
        fputs(tekst, text);
        fclose(text);
    } else { return 1; }

    text = fopen("zad3_input.txt", "r");
    if (text != NULL) {
        printf("\nFile mieszci:\n");
        while (fgets(tekst, sizeof(tekst), text)) {
            printf("%s", tekst);
        }
    } else { return 1; }

    fclose(text);
    return 0;
}
```

## Zad 4

**Treść zadania:**

Napisz program, który odczyta dane z pliku tekstowego zawierającego liczby całkowite, a następnie policzy ich sumę oraz średnią arytmetyczną. Program powinien wyświetlić na ekranie wyniki obliczeń.

**Rozwiązanie:**

```c
#include <stdio.h>

int main() {
    FILE *text;
    int N, sum = 0, cnt = 0;
    float avg;

    text = fopen("zad4.txt", "r");
    if (text != NULL) {
        while (fscanf(text, "%d", &N) != EOF) {
            sum += N;
            cnt++;
        }
    } else {
        printf("loh");
        return 1;
    }
    fclose(text);

    if (cnt > 0) {
        avg = (float)sum / cnt;
        printf("Sum: %d\n", sum);
        printf("AVG: %.2f\n", avg);
    } else {
        printf("ERROR 404.\n");
    }

    return 0;
}
```

## Zad 5

**Treść zadania:**

Napisz program, który utworzy nowy plik tekstowy i zapisze do niego listę pięciu imion i nazwisk, wczytanych z klawiatury przez użytkownika. Następnie program powinien posortować alfabetycznie listę i wyświetlić ją na ekranie.

**Rozwiązanie:**

```c
#include <stdio.h>
#include <string.h>

int main() {
    FILE *text;
    int N = 5, max_length = 100;
    char users[N][100];

    for (int i = 0; i < N; i++) {
        printf("%d: ", i + 1);
        fgets(users[i], max_length, stdin);
    }

    text = fopen("zad5.txt", "w");
    if (text != NULL) {
        for (int i = 0; i < N; i++) {
            fprintf(text, "%s\n", users[i]);
        }
    } else { return 1; }

    fclose(text);

    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (strcmp(users[i], users[j]) > 0) {
                char temp[100];
                strcpy(temp, users[i]);
                strcpy(users[i], users[j]);
                strcpy(users[j], temp);
            }
        }
    }

    printf("\nusers:\n");
    for (int i = 0; i < N; i++) {
        printf("%s\n", users[i]);
    }

    return 0;
}
```

