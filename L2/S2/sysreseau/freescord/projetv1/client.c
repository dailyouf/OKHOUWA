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
		
		
	printf(" ****** Bienvenu sur mon réseau social ****** \n");
	
	
	struct pollfd fds[2] = {
		{ .fd = 0, .events = POLLIN },
		{ .fd = sock, .events = POLLIN }
	};
	
	char ligne[LINE_MAX];
	
	char c;
	int n;
	
	while (1) {
	
		int att = poll(fds, 2, -1);
        	if (att < 0) {
            		perror("Erreur poll");
            		break;
        	}
		
		if (fds[0].revents & (POLLIN | POLLHUP)) {
			
			c = '\0';
			n = 0;
			
			do {
				c = getchar();
				ligne[n++] = c; 
			
			} while (c != '\n' && c != EOF);
			
			if (c == EOF) 
				break;
			
			ligne[n++] = '\0';
			
			lf_to_crlf(ligne);
			
			if (write(sock, ligne, n+1) < 0) {
				perror("Erreur lors de l'écriture dans la socket");
				return -1;		
			}
		}
		
		if (fds[1].revents & (POLLIN | POLLHUP)) {
			
			c = ' ';
			n = 0;
			
			while (c != '\0')  {
			
				if (read(sock, &c, 1) < 0) {
					perror("Erreur lors de la lecture de la socket");
					return -1;
				}
				
				ligne[n++] = c; 
				
			}
			
			crlf_to_lf(ligne);
			
			printf("%s", ligne);

		}
		
	}
	
	
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
