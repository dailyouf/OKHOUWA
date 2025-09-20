/* Youcef GHEDAMSI 12302243
Je déclare qu'il s'agit de mon propre travail.
Ce travail a été réalisé intégralement par un être humain. */


#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "buffer/buffer.h"
#include "utils.h"
#include <string.h>

#define PORT_FREESCORD 4321

#define LINE_MAX 512

#define BUF_SIZE 512

/** se connecter au serveur TCP d'adresse donnée en argument sous forme de
 * chaîne de caractère et au port donné en argument
 * retourne le descripteur de fichier de la socket obtenue ou -1 en cas
 * d'erreur. */
int connect_serveur_tcp(char *adresse, uint16_t port);

int main(int argc, char *argv[]){
	
	
	if (argc < 2) {
		perror("Nombre d'arguments non valide");
		return -1;
	}	
	
	int sock = connect_serveur_tcp(argv[1], PORT_FREESCORD);
	if (sock < 0)
		return -1;


	struct pollfd fds[2] = {
		{ .fd = 0, .events = POLLIN },
		{ .fd = sock, .events = POLLIN }
	};
	
	char ligne[LINE_MAX] = {0};
	
	buffer * bf0 = buff_create(0, BUF_SIZE);
	
	buffer * bf_sock = buff_create(sock, BUF_SIZE);
	
	// Affichage de la banière
	while (1) {
		
		if (buff_fgets_crlf(bf_sock, ligne, LINE_MAX) == NULL) { 
			perror("Erreur lors de la lecture de la socket");
			return 1;
		}
				
		crlf_to_lf(ligne);
				
		printf("%s", ligne);
		
		if (strcmp(ligne, "\n") == 0)
			break;
	}
	
	// Choisir un pseudo
	char response[2] = {'1'};
	
	printf("Veuillez choisir un username sous le format: 'nickname xxxxx' tel que : \n - la taille du nickname ne dépasse pas 16 charactères \n - la taille du nickname ne doit pas contenir le caractère ':' \n");
	
	while (response[0] != '0') {
		
		if (buff_fgets(bf0, ligne,  LINE_MAX) == NULL) 
				break;
			
		lf_to_crlf(ligne);
			
		if (write(sock, ligne, strlen(ligne)+1) < 0) {
			perror("Erreur lors de l'écriture dans la socket");
			return -1;		
		}
		
		if (read(sock, response, 2) < 0) {
			perror("Erreur lors de la lecture de la socket");
			return -1;		
		}
	
		switch (response[0]) {
			
			case '0':
				printf("nickname valide ! Bien joué ! \n\n");
				break;
			
			case '1':
				printf("le nickname est déjà pris par un autre utilisateur du serveur \n");
				break;
			
			case '2':
				printf("le nickname est interdit \n");
				break;
				
			case '3':
				printf("la commande ne commence pas par 'nickname' \n");
				break;
		}
	}
	
	while (1) {
	
		int att = poll(fds, 2, -1);
        	if (att < 0) {
            		perror("Erreur poll");
            		break;
        	}
		
		if (fds[0].revents & (POLLIN | POLLHUP)) {
			
			if (buff_fgets(bf0, ligne,  LINE_MAX) == NULL) 
				break;
			
			lf_to_crlf(ligne);
			
			if (write(sock, ligne, strlen(ligne)+1) < 0) {
				perror("Erreur lors de l'écriture dans la socket");
				return -1;		
			}
			
		}
		
		if (fds[1].revents & (POLLIN | POLLHUP)) {
			
			if (buff_fgets_crlf(bf_sock, ligne, LINE_MAX) == NULL) { 
				perror("Erreur lors de la lecture de la socket");
				break;
			}
			
			crlf_to_lf(ligne);
			
			printf("%s", ligne);
			fflush(stdout);

		}
		
	}
	
	buff_free(bf0);
	buff_free(bf_sock);
	
	close(sock);

	return 0;
}

int connect_serveur_tcp(char *adresse, uint16_t port) {

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("Erreur à la création de la socket");
		return -1;
	}
	
	struct sockaddr_in sa = { .sin_family=AF_INET, .sin_port=htons(port)};
	
	if (inet_pton(AF_INET, adresse, &(sa.sin_addr.s_addr)) < 0) {
		perror("Adresse ip invalide");
		return -1;
	}
	
	socklen_t sl = sizeof(sa);
	
	
	if (connect(sock, (struct sockaddr *) &sa, sl) < 0) {
		perror("Connexion au serveur impossible");
		return -1;
	}
	
	return sock;
	
}
