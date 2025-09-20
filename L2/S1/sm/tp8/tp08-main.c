#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


typedef struct rec_t {
	char name[20]; /* prenom */
	char surname[20]; /* nom */
	unsigned ine; /* INE : numero identifiant national eleve */
} rec_t;


int rec_count(int fd);

int rec_read(int fd, int n, rec_t *pr);

int rec_write(int fd, int n, rec_t *pr);

int rec_search(int fd, unsigned ine);

int main(int argc, char *argv[]) {
        int fd, go = 1;
        char fname[256];
        unsigned a;
        
        do {
                printf("Fichier des enregistrements [256 chars max] : ");
                scanf("%s", fname);

                if ((fd = open(fname, O_RDWR | O_CREAT, 0660)) == -1)
                        printf("Impossible d'ouvrir le fichier %s\n", fname);
        } while (fd == -1);

        while(go) {
                printf(">>> Choisir une action\n");
                printf("  [ 0: exit | 1: read | 2: write | 3: count ] | 4:search_ine: ");
                scanf("%u", &a);
                switch(a) {
                case 0: {
                        go = 0;
                        printf("Au revoir !\n\n");
                        break;
                }
                case 1: {
                        int n, nrec = rec_count(fd);
                        rec_t rec;
                        if (nrec == 0) {
                                printf("Le fichier est vide.\n\n");
                                break;
                        }
                        printf("Position de l'enregistrement à lire [0..%d] : ", nrec-1);
                        scanf("%d", &n);
                        if (n < 0 || n >= nrec) {
                                printf("Position de l'enregistrement non valid.\n\n");
                                break;
                        }
                        rec_read(fd, n, &rec);
                        printf("%s %s %08d\n\n", rec.name, rec.surname, rec.ine);
                        break;
                }
                case 2: {
                        int n, nrec = rec_count(fd);
                        rec_t rec;
                        printf("Position de l'enregistrement à écrire [0..%d] : ", nrec);
                        scanf("%d", &n);
                        if (n < 0 || n > nrec) {
                                printf("Position de l'enregistrement non valid.\n\n");
                                break;
                        }
                        printf("Prénom : ");
                        scanf("%s", rec.name);
                        printf("Nom : ");
                        scanf("%s", rec.surname);
                        printf("INE : ");
                        scanf("%d", &rec.ine);
                        rec_write(fd, n, &rec);
                        printf("%s %s %08d\n\n", rec.name, rec.surname, rec.ine);
                        break;
                }
                case 3: {
                        int nrec = rec_count(fd);
                        printf("Le fichier contient %d enregistrements.\n\n", nrec);
                        break;
                }
                case 4: {
			int n;
			unsigned ine;
			printf("Entrer l'INE : ");
			scanf("%u", &ine);
			if ((n = rec_search(fd, ine)) == -1) {
				printf("Aucun enregistrement avec INE %u dans le fichier.\n",
				       ine);
			} else {
				rec_t rec;
				int m = rec_read(fd, n, &rec);
				printf("Enregistrement en position %u\n%s %s %08d\n\n",
				       n, rec.name, rec.surname, rec.ine);
			}
			break;
		    }
		    default:
			printf("%d n'est une action connue.\n", a);
		}
        }
        
        close(fd);
        
        return EXIT_SUCCESS;
}


int rec_count(int fd) {
	
	int taille = lseek(fd, 0, SEEK_END);	
	
	return taille / sizeof(struct rec_t);
}

int rec_read(int fd, int n, rec_t *pr) {

	lseek(fd, n*sizeof(struct rec_t), SEEK_SET);
	
	if (read(fd, pr, sizeof(struct rec_t)) == sizeof(struct rec_t)) {
		return 1;
	}else {
		return 0;
	}
}

int rec_write(int fd, int n, rec_t *pr) {
	
	lseek(fd, n*sizeof(struct rec_t), SEEK_SET);
	
	if (write(fd, pr, sizeof(struct rec_t)) == sizeof(struct rec_t)) {
		return 1;
	}else {
		return 0;
	}

}


int rec_search(int fd, unsigned ine) {
	
	struct rec_t * tmp;
	int n=0;
	
	lseek(fd, 0, SEEK_SET);
	
	while (read(fd, tmp, sizeof(struct rec_t)) > 0) {
			
		if (tmp->ine == ine) {
			return n;
		}
		
		n++;
	
	 }
	
	return -1;
	
}


