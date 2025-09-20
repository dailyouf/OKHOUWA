#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "tp12-1.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int add1odd(char *fname);
int generate(char *fname, int n);
int affiche(char *fname);

int main(int argc, char *argv[]) {
        char *fname = "values.bin";
        if (generate(fname, 20) == -1)
                printf("Impossible d’ouvrir le fichier %s\n", fname);
        if (affiche(fname) == -1)
                printf("Impossible d’ouvrir le fichier %s\n", fname);
        if (add1odd(fname) == -1)
                printf("Impossible d’ouvrir le fichier %s\n", fname);
        if (affiche(fname) == -1)
                printf("Impossible d’ouvrir le fichier %s\n", fname);
        return EXIT_SUCCESS;
}

/*
 * Définition des fonctions generate et affiche
 */
int generate(char *fname, int n) {
        int fd, i, v;

        if ((fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
                return -1;
        srandom(time(NULL));
        for (i = 0; i < n; i++) {
                v = random() % 1024;
                write(fd, &v, sizeof(int));
        }
        close(fd);
        return 0;
}

int affiche(char *fname) {
        int fd, v;

        if ((fd = open(fname, O_RDONLY)) == -1)
                return -1;
        while (read(fd, &v, sizeof(int)) > 0)
                printf("%d ", v);
        printf("\n");
        close(fd);
        return 0;
}

