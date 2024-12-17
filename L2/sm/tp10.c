#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void exo1();
void exo2();

int findMin(int arr[], int size);
int findMax(int arr[], int size);
float calculateAverage(int arr[], int size);

int main() {
        exo1();
        return EXIT_SUCCESS;
}

void exo1() {
        int fd[2], pid;

        pipe(fd);

        pid = fork();

        if (pid == 0) {
                close(fd[0]);
                dup2(fd[1], 1);
                execl("/bin/ps", "ps", "-aj", NULL);
        } else {
                pid = fork();
                if (pid == 0) {
                        close(fd[1]);
                        dup2(fd[0], 0);
                        execl("/bin/tr", "tr", "[:upper:][:lower:]", "[:lower:][:upper:]", NULL);
                } else {
                        close(fd[0]);
                        close(fd[1]);
                }
        }
}

void exo2() {
        int fd1[2], fd2[2], pid;

        pipe(fd1);
        pipe(fd2);

        pid = fork();

        if (pid == 0) {
                int lgf, j, min, max, *values;
                float moy;

                close(fd1[1]);
                close(fd2[0]);

                read(fd1[0], &lgf, sizeof(int));

                values = malloc(lgf * sizeof(int));

                for (j = 0; j < lgf; j++) {
                        read(fd1[0], values + j, sizeof(int));
                }

                min = findMin(values, lgf);
                write(fd2[1], &min, sizeof(int));

                max = findMax(values, lgf);
                write(fd2[1], &max, sizeof(int));

                moy = calculateAverage(values, lgf);
                write(fd2[1], &moy, sizeof(float));

                close(fd1[0]);
                close(fd2[1]);
        } else {
                int length, vp, i, minp, maxp;
                float moyp;

                close(fd1[0]);
                close(fd2[1]);

                printf("Veuillez entrer la longueur de la séquence: ");
                scanf("%d", &length);

                write(fd1[1], &length, sizeof(int));

                for (i = 0; i < length; i++) {
                        printf("Veuillez entrer la %d eme valeur: ", i + 1);
                        scanf("%d", &vp);
                        write(fd1[1], &vp, sizeof(int));
                }

                read(fd2[0], &minp, sizeof(int));
                printf("Minimum: %d\n", minp);

                read(fd2[0], &maxp, sizeof(int));
                printf("Maximum: %d\n", maxp);

                read(fd2[0], &moyp, sizeof(float));
                printf("Average: %.2f\n", moyp);

                close(fd1[1]);
                close(fd2[0]);
        }
}

int findMin(int arr[], int size) {
        int min = arr[0];
        for (int i = 1; i < size; i++) {
                if (arr[i] < min) {
                        min = arr[i];
                }
        }
        return min;
}

int findMax(int arr[], int size) {
        int max = arr[0];
        for (int i = 1; i < size; i++) {
                if (arr[i] > max) {
                        max = arr[i];
                }
        }
        return max;
}

float calculateAverage(int arr[], int size) {
        int sum = 0;
        for (int i = 0; i < size; i++) {
                sum += arr[i];
        }
        return (float) sum / size;
}

