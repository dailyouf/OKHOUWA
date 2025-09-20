#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSZ 256

int main() {
	
	int fd = open("lol.txt", O_RDONLY);

	ssize_t n; /* signed size type pour pouvoir accueillir -1 */

	char buffer[BUFSZ];

	if (fd < 0) {
		perror("open");
		return 1;
	}

	printf("Descripteur de fichier : %d\n", fd);
	
	n = read(fd, buffer, 4);
	// buffer[n] = '\0';
	printf("n = %ld\n", n);
	
	// printf("octet 0 du fichier : %c\n", buffer[0]);
	// printf("les %ld premiers octets du fichier : %s \n", n, buffer);
	write(1, buffer, n);
	write(1, "\n", 1);
	
	n = read(fd, buffer, 4);
	// buffer[n] = '\0';
	printf("n = %ld\n", n);
	//printf("octet 1 du fichier : %c\n", buffer[0]);
	// printf("les %ld derniers octets du fichier : %s \n", n, buffer);
	write(1, buffer, n);
	write(1, "\n", 1);
	
	
	n = read(fd, buffer, 20);
	buffer[n] = '\0';
	printf("n = %ld\n", n);	
	// printf("Contenu du buffer: %s \n", buffer);
	write(1, buffer, n);
	write(1, "\n", 1);
	
	
	n = read(fd, buffer, 1);
	printf("n = %ld\n", n);


	close(fd);
	
	return 0;
}
