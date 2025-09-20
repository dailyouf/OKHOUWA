/* fichiers de la bibliothèque standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
/* bibliothèque standard unix */
#include <unistd.h> /* close, read, write */
#include <sys/types.h>
#include <sys/socket.h>
/* spécifique à internet */
#include <arpa/inet.h> /* inet_pton */

#include "sys_utils.h"
#define PORT_QUIZZP 6666
#define L_LIGNE 256 /* Longueur maximale d'une ligne dans une question */

void usage(char *nom_prog)
{
	fprintf(stderr, "Usage: %s addr_ipv4\n"
			"client pour QUIZZP (Quizz Protocol)\n"
			"Exemple: %s 127.0.0.1 \n", nom_prog, nom_prog);
}

/** Essayer de se connecter en TCP à l'adresse IPv4 donnée en argument, au port
 * associé au Quizz Protocol.
 *
 * En cas de succès, retourne le descripteur de fichier associé à la socket
 * d'échange avec le serveur.
 * En cas d'échec, met fin au programme après avoir affiché un message d'erreur
 * sur la sortie standard des erreurs. */
int connection_au_serveur(const char *addr_ipv4);

/** Échanger avec le serveur connecté via la socket sock ainsi que spécifié par
 * le protocole Quizz Protocol, tout en menant les échanges avec l'utilisateur.
 *
 * - Imprimer sur la sortie standard la question et les propositions envoyées
 *   par le serveur
 * - Demander à l'utilisateur un entier entre 1 et le nombre de propositions
 * - Envoyer le numéro de la réponse choisie au serveur
 * - Recevoir le message final du serveur (réponse correcte ou incorrecte)
 * - Dire à l'utilisateur si sa réponse est correcte ou non
 */
void echanger_avec_serveur(int sock);
void echanger_avec_serveur_test(int sock);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		usage(argv[0]);
		return 1;
	}
	int sock = connection_au_serveur(argv[1]);
	echanger_avec_serveur(sock);
	close(sock);
	return 0;
}

int connection_au_serveur(const char *addr_ipv4) {	
	
	
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror_exit("Erreur à la création de la socket");
	}
	
	struct sockaddr_in sa = { .sin_family = AF_INET, .sin_port = htons(PORT_QUIZZP) }; 
	
	/* "Internet Presentation to Numeric" convertit une représentation
	 * d'adresse IP (v4 ou v6) en numérique (gros-boutiste) */
	if (inet_pton(AF_INET, addr_ipv4, &sa.sin_addr) == -1) {
		perror_exit("Adresse ipv4 non valable");
	}
	
	int sl = sizeof(sa);
	
	
	if (connect(sock, (struct sockaddr *) &sa, sl) < 0) {
		perror_exit("Connection serveur impossible");
	}	
	
	
	return sock;
	
}

void echanger_avec_serveur(int sock) {

	
	char message[L_LIGNE];
	
	uint16_t nb_props, nb_props_n;
	
	uint16_t response, response_n;
	uint8_t res;

	
	if (exact_read(sock, &nb_props_n, sizeof(nb_props_n)) == -1) {
		perror_exit("Erreur lors de la lecture du nombre de proposition");
	}
	
	nb_props = ntohs(nb_props_n);
	
	char c = '1';
	int total = 0;
	while (c != '\0') {
		if (exact_read(sock, &c, 1) == -1) {
			perror_exit("Erreur lors de la lecture de l'énoncé");
		}
		message[total] = c;
		total++;
	}
	
	printf("%s \n", message);
	
	for (int i=0; i<nb_props; i++) {
		
		c = '1';
		total = 0;
		
		while (c != '\0') {
			if (exact_read(sock, &c, 1) == -1) {
				perror_exit("Erreur lors de la lecture des proposition");
			}
			message[total] = c;
			total++;
		}
		
		printf("%d. %s \n", i+1, message);
	 
	}
	
	response = saisir_entre_bornes(1, nb_props);
	
	response_n = htons(response);
 	if (write(sock, &response_n, sizeof(response_n)) < 0) {
	      	perror_exit("Erreur lors de l'envoi de la réponse");
	}
	
	if (exact_read(sock, &res, 1) == -1) {
		perror_exit("Erreur lors de la lecture du résultat");
	}
	
	
	if (res == 1) 
		printf("Bravo, c'est la bonne réponse !  \n");
	
	else 
		printf("Désolé, ce n'est pas la bonne réponse. \n");
	
	
	close(sock);

}
































