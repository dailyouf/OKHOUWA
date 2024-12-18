#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

        if (argc != 4) {
                fprintf(stderr, "Usage: %s <fichier_in> <mot> <fichier_out>\n", argv[0]);
                return EXIT_FAILURE;
        }

        char *fin = argv[1];
        char *mot = argv[2];
        char *fout = argv[3];

        int fd[2];
        pid_t p1, p2; 

        // Création du pipe
        if (pipe(fd) == -1) {
                perror("pipe");
                return EXIT_FAILURE;
        }

        // Ouverture du fichier de sortie
        int fout_fd = open(fout, O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (fout_fd == -1) {
                perror("open");
                return EXIT_FAILURE;
        }

        // Premier processus : cat <fin>
        if ((p1 = fork()) == -1) {
                perror("fork");
                return EXIT_FAILURE;
        }
        if (p1 == 0) {
                close(fd[0]);                   // Fermer la lecture du pipe
                dup2(fd[1], 1);                 // Rediriger stdout vers le pipe
                close(fd[1]);
                close(fout_fd);
                execl("/usr/bin/cat", "cat", fin, NULL);
                perror("execlp cat");           // En cas d'erreur
                exit(EXIT_FAILURE);
        }

        // Deuxième processus : grep <mot> > fout
        if ((p2 = fork()) == -1) {
                perror("fork");
                return EXIT_FAILURE;
        }
        if (p2 == 0) {
                close(fd[1]);                   
                dup2(fd[0], 0);      
                dup2(fout_fd, 1);   
                close(fd[0]);
                close(fout_fd);
                execl("/usr/bin/grep", "grep", mot, NULL);
                perror("execlp grep");        
                exit(EXIT_FAILURE);
        }

        close(fd[0]);
        close(fd[1]);
        close(fout_fd);

        wait(&p1);
        wait(&p2);

        return EXIT_SUCCESS;
}

