#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


void string_to_uint32_and_cidr(char *src, uint32_t * addr, uint8_t *cidr);

void uint32_to_string(uint32_t ipv4, char *dest);

int main(int argc, char * argv[]) {

	uint32_t addr, mask, addr_reseau, n_machine, addr_broad;
	
	uint8_t cidr;
	
	char * ip_adress = malloc(16 * sizeof(unsigned char));
	char * mask_adress = malloc(16 * sizeof(unsigned char));
	char * reseau_adress = malloc(16 * sizeof(unsigned char));
	char * broad_adress = malloc(16 * sizeof(unsigned char));			
	
	for (int i=1; i<argc; i++) {
	
		string_to_uint32_and_cidr(argv[i], &addr, &cidr);
		
		uint32_to_string(addr, ip_adress);
		
		mask = 0xFFFFFFFF << (32 - cidr);
		
		addr_reseau = addr & mask;
		n_machine = addr & ~mask;
		addr_broad = addr | ~mask;
		
		uint32_to_string(mask, mask_adress);
		uint32_to_string(addr_reseau, reseau_adress);
		uint32_to_string(addr_broad, broad_adress);
		
		printf("adresse ipv4 : %s \n", ip_adress);
		printf("masque de sous-réseau : %s\n", mask_adress);
	        printf("adresse du réseau : %s\n", reseau_adress);
	        printf("Numéro de la machine dans le réseau : %u\n", n_machine);
	        printf("adresse de broadcast dans le réseau : %s\n", broad_adress);
        
		
	}


	return EXIT_SUCCESS;
}


void string_to_uint32_and_cidr(char *src, uint32_t * addr, uint8_t *cidr) {

	uint8_t a, b, c, d;
	
	if (sscanf(src, "%hhu.%hhu.%hhu.%hhu/%hhu", &a, &b, &c, &d, cidr) != 5) {
		
		perror("lecture adresse ip: ");
		exit(1);

	}
	
	
	*addr = (a << 24) | (b << 16) | (c << 8) | d;	
	
}



void uint32_to_string(uint32_t ipv4, char *dest) {

	if (sprintf(dest, "%hhu.%hhu.%hhu.%hhu", (ipv4 >> 24), (ipv4 >> 16), (ipv4 >> 8), ipv4) == 100) {
		
		perror("écriture adresse ip: ");
		exit(1);
	
	}

}
