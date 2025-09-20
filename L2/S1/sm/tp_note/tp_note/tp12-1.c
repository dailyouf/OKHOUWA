#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// Fonction pour déterminer le nombre de positions où deux fichiers binaires ont des valeurs
// du même signe (positives, négatives ou nulles).
int accord_signes(char *fname1, char *fname2) {
        int fdin1, fdin2, fdout;    // Descripteurs de fichiers pour les fichiers d'entrée et de sortie
        int value1, value2;        // Variables pour stocker les valeurs lues des fichiers
        int i = 0;                 // Indice de position dans les fichiers
        int nb = 0;                // Compteur du nombre d'accords de signe

        // Ouvrir le premier fichier en lecture seule
        if ((fdin1 = open(fname1, O_RDONLY)) == -1) {
                perror("Erreur lors de l'ouverture du fichier fname1");
                return -1;
        }

        // Ouvrir le second fichier en lecture seule
        if ((fdin2 = open(fname2, O_RDONLY)) == -1) {
                perror("Erreur lors de l'ouverture du fichier fname2");
                close(fdin1);  // Assurer la fermeture du premier fichier avant de quitter
                return -1;
        }

        // Ouvrir ou créer le fichier de sortie, avec des permissions pour lecture et écriture
        if ((fdout = open("out.bin", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR)) == -1) {
                perror("Erreur lors de la création du fichier out.bin");
                close(fdin1);
                close(fdin2);
                return -1;
        }

        // Lire simultanément les fichiers et comparer les valeurs
        while ((read(fdin1, &value1, sizeof(int)) > 0) &&
               (read(fdin2, &value2, sizeof(int)) > 0)) {
                // Vérifier si les deux valeurs ont le même signe ou sont toutes les deux nulles
                if (((value1 == 0) && (value2 == 0)) ||
                    ((value1 > 0) && (value2 > 0)) ||
                    ((value1 < 0) && (value2 < 0))) {
                        // Écrire l'indice i dans le fichier de sortie
                        if (write(fdout, &i, sizeof(int)) == -1) {
                                perror("Erreur lors de l'écriture dans le fichier out.bin");
                                close(fdin1);
                                close(fdin2);
                                close(fdout);
                                return -1;
                        }
                        nb++;  // Incrémenter le compteur d'accords
                }
                i++;  // Avancer l'indice
        }

        // Fermer les fichiers après utilisation
        if (close(fdin1) == -1) {
                perror("Erreur lors de la fermeture de fname1");
                return -1;
        }

        if (close(fdin2) == -1) {
                perror("Erreur lors de la fermeture de fname2");
                return -1;
        }

        if (close(fdout) == -1) {
                perror("Erreur lors de la fermeture de out.bin");
                return -1;
        }

        return nb;  // Retourner le nombre d'accords trouvés
}

