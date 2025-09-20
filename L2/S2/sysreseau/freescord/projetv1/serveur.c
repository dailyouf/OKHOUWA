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

#define PORT_FREESCORD 4321

#define BUFFER 512

#define MAX_LIGNE 512


int tube[2];

struct list * list_users;

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
	
	
	while (1) {
		
		struct user * user = user_accept(sock);
		
		list_users = list_add(list_users, user);
		
		if (pthread_create(user->thread, NULL, handle_client, user) < 0) {
			perror("Erreur à la création du thread");
			return -1;		
		}
		
		if (pthread_detach(*(user->thread)) < 0) {
			perror("Erreur lors du détachement du thread");
			return -1;
		}
			
		
	}
	
	close(sock);
	
	return 0;
}

void * handle_client(void * arg) {

	struct user * user = arg;
	
	ssize_t n = 1;
	
	char ligne[MAX_LIGNE];
	
	char c;
	int i;
	
	while (n != 0) {
		
		c = ' ';
		i = 0;
		
		while (c != '\0' && n != 0) {
			
			n = read(user->sock, &c, 1);	
			
			ligne[i++] = c;
		
		}
	
		if (write(tube[1], ligne, i) < 0) {
			perror("Erreur lors de l'envoi des données au client");
			return NULL;
		}
		
		last_user = user;
		
	}
	
	close(user->sock);
	
	list_remove_element(list_users, user);
	
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
	
	char ligne[MAX_LIGNE];
	
	struct user * user;
	
	char c;
	int i;
	int n=1;
	
	while(1) {
		
		c = ' ';
		i = 0;
		
		while (c != '\0' && n != 0) {
			
			n = read(tube[0], &c, 1);	
			
			ligne[i++] = c;
		
		}
		
			
		for (int j=0; j<list_length(list_users); j++) {
			
			user = list_get(list_users, j);
			
			if (user == last_user)
				continue;
		
		
			if (write(user->sock, ligne, i) < 0) {
				perror("Erreur lors de l'envoi des données au client");
				return NULL;
			}
		
		}
		
		
	}


}
