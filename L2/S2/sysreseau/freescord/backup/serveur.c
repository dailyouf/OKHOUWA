#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list/list.h"
#include "user.h"
#include "buffer/buffer.h"

#define PORT_FREESCORD 4321

#define LIGNE_MAX 512

#define BUF_SIZE 512


pthread_mutex_t wr_tb;
int tube[2];


pthread_mutex_t ls_usr;
struct list * list_users;


pthread_mutex_t lt_usr;
// last user who wrote a message
struct user * last_user;


/** Gérer toutes les communications avec le client renseigné dans
 * user, qui doit être l'adresse d'une struct user */
void *handle_client(void *user);

/** Créer et configurer une socket d'écoute sur le port donné en argument
 * retourne le descripteur de cette socket, ou -1 en cas d'erreur */
int create_listening_sock(uint16_t port);

void * handle_repeteur(void * arg);

int main(int argc, char *argv[]) {
	
	int sock = create_listening_sock(PORT_FREESCORD);
	if (sock < 0)
		return -1;

	pipe(tube);
	
	list_users = list_create();
	
	pthread_t rep;
	
	if (pthread_create(&rep, NULL, handle_repeteur, NULL) < 0) {
		perror("Erreur à la création du thread répéteur");
		return -1;		
	}
		
	if (pthread_detach(rep) < 0) {
		perror("Erreur lors du détachement du thread répéteur");
		return -1;
	}
	
	if (pthread_mutex_init(&wr_tb, NULL) < 0) {
		perror("Erreur lors de la créaction du mutex");
		return -1;
	}
	
	if (pthread_mutex_init(&ls_usr, NULL) < 0) {
		perror("Erreur lors de la créaction du mutex");
		return -1;
	}
	
	if (pthread_mutex_init(&lt_usr, NULL) < 0) {
		perror("Erreur lors de la créaction du mutex");
		return -1;
	}
	
	while (1) {
		
		struct user * user = user_accept(sock);
		
		pthread_mutex_lock(&ls_usr);
		list_users = list_add(list_users, user);
		pthread_mutex_unlock(&ls_usr);
		
		if (pthread_create(user->thread, NULL, handle_client, user) < 0) {
			perror("Erreur à la création du thread");
			return -1;		
		}
		
		if (pthread_detach(*(user->thread)) < 0) {
			perror("Erreur lors du détachement du thread");
			return -1;
		}
			
		
	}
	
	pthread_mutex_destroy(&wr_tb);
	pthread_mutex_destroy(&ls_usr);
	pthread_mutex_destroy(&lt_usr);
	
	close(sock);
	
	return 0;
}

void * handle_client(void * arg) {

	struct user * user = arg;
	
	ssize_t n = 1;
	
	char ligne[LIGNE_MAX];
	
		
	buffer * bf0 = buff_create(user->sock, BUF_SIZE);
	
	while (n != 0) {
		
		if (buff_fgets_crlf(bf0, ligne, LIGNE_MAX) == NULL) { 
			perror("Erreur lors de la lecture du tube");
			break;
		}
		
		printf("%d", ligne[0]);
		
		pthread_mutex_lock(&wr_tb);
		if (write(tube[1], ligne, strlen(ligne)+1) < 0) {
			perror("Erreur lors de l'envoi des données au client");
			return NULL;
		}
		pthread_mutex_unlock(&wr_tb);
		
		pthread_mutex_lock(&lt_usr);
		last_user = user;
		pthread_mutex_unlock(&lt_usr);
		
		
	}
	
	close(user->sock);
	
	pthread_mutex_lock(&ls_usr);
	list_remove_element(list_users, user);
	pthread_mutex_unlock(&ls_usr);
	
	user_free(user);
	
	return NULL;
}


int create_listening_sock(uint16_t port){

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("Erreur à la création de la socket");
		return -1;
	}
	
	
	struct sockaddr_in sa = { .sin_family=AF_INET, .sin_port=htons(port), .sin_addr.s_addr=htons(INADDR_ANY)};
	
	socklen_t sl = sizeof(sa);
	
	
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
	
	
	if (bind(sock, (struct sockaddr *) &sa, sl) < 0) {
		perror("Erreur lors du bind");
		return -1;
	}
	
	
	if (listen(sock, 128) < 0) {
		perror("Erreur lors du listen");
		return -1;
	}
	
	
	return sock;
}


void * handle_repeteur(void * arg) {
	
	char ligne[LIGNE_MAX];
	
	struct user * user;
	
	buffer * bf0 = buff_create(tube[0], BUF_SIZE);
	
	int l;
	
	while(1) {
		
		if (buff_fgets_crlf(bf0, ligne, LIGNE_MAX) == NULL) { 
			perror("Erreur lors de la lecture du tube");
			break;
		}
			
		pthread_mutex_lock(&ls_usr);
		l = list_length(list_users);
		pthread_mutex_unlock(&ls_usr);
			
		for (int j=0; j<l; j++) {
			
			pthread_mutex_lock(&ls_usr);
			user = list_get(list_users, j);
			pthread_mutex_unlock(&ls_usr);
			
			pthread_mutex_lock(&ls_usr);
			if (user == last_user) {
				pthread_mutex_unlock(&ls_usr);
				continue;
			}	
			
			if (write(user->sock, ligne, strlen(ligne)+1) < 0) {
				perror("Erreur lors de l'envoi des données au client");
				return NULL;
			}
		
		}
		
		
	}

	return NULL;
}
