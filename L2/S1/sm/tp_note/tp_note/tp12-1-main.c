#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int accord_signes(char *fname1, char *fname2);

int generate(char *fname, int n);

int affiche(char *fname);

int main(int argc, char *argv[]) {
  char *finname1 = "values1.bin";
  char *finname2 = "values2.bin";
  char *foutname = "out.bin";
  int n;

  if (generate(finname1, 30) == -1) {
    printf("Impossible d'ouvrir le fichier %s\n", finname1);
    return EXIT_FAILURE;
  }
  
  if (affiche(finname1) == -1) {
    printf("Impossible d'ouvrir le fichier %s\n", finname1);
    return EXIT_FAILURE;
  }

  if (generate(finname2, 32) == -1) {
    printf("Impossible d'ouvrir le fichier %s\n", finname2);
    return EXIT_FAILURE;
  }
  
  if (affiche(finname2) == -1) {
    printf("Impossible d'ouvrir le fichier %s\n", finname2);
    return EXIT_FAILURE;
  }

  if ((n = accord_signes(finname1, finname2)) == -1) {
    printf("Impossible d'ouvrir le fichier %s ou %s\n", finname1, finname2);
        return EXIT_FAILURE;
  }

  printf("Nombre d'accords : %d\n", n);
    
  printf("Liste des accords :\n");
  
  if (affiche(foutname) == -1) {
    printf("Impossible d'ouvrir le fichier %s\n", foutname);
    return EXIT_FAILURE;
  }
  
  printf("Bye!\n");
  return EXIT_SUCCESS;
}

/*
 * Définition des fonctions generate et affiche
 */

int generate(char *fname, int n) {
  static int first = -1;
  if (first) {
    srand(time(NULL));
    first = 0;
  }

  int fd, i;
  if ((fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
    return -1;
  for (i = 0; i < n; i++) {
    int v = (rand() % MAX) - (MAX / 2);
    write(fd, &v, sizeof(int));
  }
  close(fd);
  return 0;
}

int affiche(char *fname) {
  int fd;
  if ((fd = open(fname, O_RDONLY)) == -1)
    return -1;
  int v;
  while (read(fd, &v, sizeof(int)) > 0)
    printf("%d ", v);
  printf("\n");
  close(fd);
  return 0;
}
