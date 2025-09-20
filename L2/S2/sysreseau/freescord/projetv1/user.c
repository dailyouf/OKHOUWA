#include "user.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>	

/** accepter une connection TCP depuis la socket d'écoute sl et retourner un
 * pointeur vers un struct user, dynamiquement alloué et convenablement
 * initialisé */
struct user *user_accept(int sl) {

	struct user * user = malloc(sizeof(struct user));
	
	user->address = malloc(sizeof(socklen_t));

	user->sock = accept(sl, user->address, &(user->addr_len));
	if (user->sock < 0) {
		perror("Erreur à l'acceptation de la connexion tcp");
		return NULL;	
	}
	
	user->thread = malloc(sizeof(pthread_t));
	
	return user;
}

/** libérer toute la mémoire associée à user */
void user_free(struct user *user) {
	
	free(user->address);
	
	free(user->thread);
	
	free(user);
}
