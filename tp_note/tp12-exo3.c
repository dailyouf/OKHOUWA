#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
        // Déclaration des variables
        int fd[2];      // Tableau pour stocker les descripteurs de pipe
        int n1, n2;     // Entiers pour stocker les valeurs lues de l'utilisateur
        int a;          // Variable pour stocker les valeurs lues depuis le pipe

        // Demander à l'utilisateur d'entrer les valeurs n1 et n2
        do{
		printf("Entrez n1:\n");
		scanf("%d", &n1);  // Lecture de n1
		printf("Entrez n2:\n");
		scanf("%d", &n2);  // Lecture de n2
        }while(n1 < 0 || n2 < 0);

        // Création du pipe pour la communication entre processus
        if (pipe(fd) == -1) {  // Si la création du pipe échoue
                perror("Erreur lors  de la creation du pipe");
                return EXIT_FAILURE;  // Sortie du programme en cas d'erreur
        }

        pid_t fils1, fils2;  // Déclaration des identifiants des processus fils

        // Création du premier processus fils (fils1)
        fils1 = fork();
        if (fils1 == -1) {  // Si la création du processus échoue
                perror("Erreur lors de la creation du fils 1");
                return EXIT_FAILURE;  // Sortie du programme en cas d'erreur
        }

        if (fils1 == 0) {  // Code exécuté par le premier processus fils
                int value = 1;  // Valeur initiale pour le premier fils
                close(fd[0]);  // Fermer le descripteur de lecture du pipe dans le fils
                
                // Écriture dans le pipe, de 1 à n1
                while (value <= n1) {
                        if (write(fd[1], &value, sizeof(int)) == -1) {  // Écriture dans le pipe
                                perror("Erreur dans l'ecriture du fils 1");
                                return EXIT_FAILURE;  // Sortie en cas d'erreur d'écriture
                        }
                        value++;  // Incrémentation de la valeur
                }
                close(fd[1]);  // Fermer le descripteur d'écriture du pipe
                return EXIT_SUCCESS;  // Sortie du premier fils
        }

        // Création du deuxième processus fils (fils2)
        fils2 = fork();
        if (fils2 == -1) {  // Si la création du processus échoue
                perror("Erreur lors de la creation du fils 2");
                return EXIT_FAILURE;  // Sortie du programme en cas d'erreur
        }

        if (fils2 == 0) {  // Code exécuté par le deuxième processus fils
                close(fd[0]);  // Fermer le descripteur de lecture du pipe dans le fils
                int value = -1;  // Valeur initiale pour le deuxième fils
                
                // Écriture dans le pipe, de -1 à -n2
                while (value >= -n2) {
                        if (write(fd[1], &value, sizeof(int)) == -1) {  // Écriture dans le pipe
                                perror("Erreur dans l'ecriture du fils 2");
                                return EXIT_FAILURE;  // Sortie en cas d'erreur d'écriture
                        }
                        value--;  // Décrémentation de la valeur
                }
                close(fd[1]);  // Fermer le descripteur d'écriture du pipe
                return EXIT_SUCCESS;  // Sortie du deuxième fils
        }

        // Code exécuté par le processus père
        close(fd[1]);  // Fermer le descripteur d'écriture du pipe dans le père

        // Attendre que les deux processus fils se terminent
        wait(&fils1);  // Attente de la fin du premier fils
        wait(&fils2);  // Attente de la fin du deuxième fils

        // Lecture des valeurs du pipe et affichage
        while (read(fd[0], &a, sizeof(int)) > 0) {
                printf("%d\n", a);  // Affichage des valeurs lues depuis le pipe
        }

        close(fd[0]);  // Fermer le descripteur de lecture du pipe dans le père

        return EXIT_SUCCESS;  // Fin du programme
}

