/* fichiers de la bibliothèque standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* bibliothèque standard unix */
#include <unistd.h> /* close, read, write */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* spécifique à internet */
#include <arpa/inet.h> /* inet_pton */
/* threads */
#include <pthread.h>

#include "sys_utils.h"
#include "question.h"

#define PORT_QUIZZP 6666
#define FICH_QUESTIONS "questionnaire.txt"
#define L_LIGNE 256 /* Longueur maximale d'une ligne dans une question */

#define MONO 1

/* Pour pouvoir partager les tâches entre différents threads (en fin d'énoncé) */
struct work {
	int socket;
	struct question *q;
};

/** Créer et configure une socket d'écoute TCP sur IPv4 sur le port associé au
 * Quizz Protocol. Retourne le descripteur de fichier de la socket ainsi créée
 * en cas de succès, met fin au programme sinon. */
int init_sock_ecoute();

/** Accepter les demandes de connection entrantes sur la socket d'écoute
 * sock.
 * Retourne le descripteur de fichier de la socket d'échange créée ou -1 en cas
 * d'erreur */
int connection_au_client(int sock);

/** Recevoir l'adresse d'une variable de type struct work convenablement
 * initialisée, puis échanger avec un client en utilisant le champ socket de
 * cette structure pour la question (champ q) de cette strucure.
 * Retourne : toujours NULL. */
void *worker(void *work);

/* Mener tous les échanges avec le client connecté à la socket fd, ainsi que 
 * spécifié dans le Quizz Protocol, avec la question d'adresse q */
void echanger_avec_client(int fd, const struct question *q);
void echanger_avec_client_test(int fd, const struct question *q);


int main() {
	
	struct banque_questions *bq = init_banque_questions(FICH_QUESTIONS);
	int sock = init_sock_ecoute();

	for (;;) {
	
		int se = connection_au_client(sock);
		if (se < 0)
			continue;
		
		struct work sw = {.socket=se, .q=question_aleatoire(bq)};
		
		pthread_t th;
		
		if (pthread_create(&th, NULL, worker, &sw) == -1) {
			perror_exit("Erreur à la création du thread");			
		}

		if (pthread_detach(th) == -1) {
			perror_exit("Erreur au detach du thread");
		}
	
	}


	close(sock);

	detruire_banque_questions(bq);

	return 0;
}

int init_sock_ecoute() {
	
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror_exit("Erreur à la création de la socket");
	}

	struct sockaddr_in sa = { .sin_family = AF_INET, .sin_port = htons(PORT_QUIZZP), .sin_addr.s_addr = htonl(INADDR_ANY) };
	
	int sl = sizeof(sa);
	
	/* Optionnel : faire en sorte de pouvoir réutiliser l'adresse sans
	* attendre après la fin du serveur. */
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
	
	
	if (bind(sock, (struct sockaddr *) &sa, sl) < 0) {
		perror_exit("Erreur au bind");
	}
	
	if (listen(sock, 128) < 0) {
		perror_exit("Erreur au listen");
	}	
	
	
	return sock;

}

int connection_au_client(int sock){
	
	
	struct sockaddr_in sa;
	unsigned sl = sizeof(sa);
	
	int new_socket = accept(sock, (struct sockaddr *) &sa, &sl);
		
	if (new_socket < 0) {
		perror_exit("Impossible d'accepter la requet");
	}
	
	
	char ip_address[INET_ADDRSTRLEN];
    	if (inet_ntop(AF_INET, &sa.sin_addr, ip_address, sizeof(ip_address)) == NULL) {
        	perror("inet_ntop");
    	} else {
        	printf("Connection au client : %s\n", ip_address);
    	}
	
	
	return new_socket;	

}




void *worker(void *work) {
	
	struct work * sw = work;
	
	echanger_avec_client(sw->socket, sw->q);
	
	
	return NULL;	
	
}

void echanger_avec_client(int fd, const struct question *q) {

	uint16_t nb_props_n = htons(q->nb_props);
	uint16_t received_n, received;

	uint8_t res;
	
	if (write(fd, &nb_props_n, sizeof(nb_props_n)) < 0) {
		perror_exit("Erreur lors de l'envoi du nb de propositions");
	}
	
	if (write(fd, q->enonce, strlen(q->enonce) + 1) < 0) {
		perror_exit("Erreur lors de l'envoi de l'énoncé");
	}
	
	for (int i=0; i<q->nb_props; i++) {
	
		if (write(fd, q->propositions[i], strlen(q->propositions[i]) + 1) < 0) {
			perror_exit("Erreur lors des propositions");
		}
	
	}
	
	if (exact_read(fd, &received_n, sizeof(received_n)) == -1) {
		perror_exit("Erreur lors de la réponse du client ");
	}
	
	
	received = ntohs(received_n);
	
	res = (received == q->ind_rep) ? 1 : 0;
	
	
	if (write(fd, &res, 1) < 0) {
		perror_exit("Erreur lors de l'envoi du résultat");
	}
	
	
	close(fd);	

}


































