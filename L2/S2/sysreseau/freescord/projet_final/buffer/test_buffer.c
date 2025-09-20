/* Youcef GHEDAMSI 12302243
Je déclare qu'il s'agit de mon propre travail.
Ce travail a été réalisé intégralement par un être humain. */

#include "buffer.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define TEST_FILE "test.txt"
#define BUFF_SZ   8

void write_test_file(char * content);


int main() {
	
	int fd, c;
	
	buffer *b;
	
	char dest[64], line_crlf[64], *res;

	write_test_file("Ligne1\nLigne2\r\nFin");

	
	fd = open(TEST_FILE, O_RDONLY);
	assert(fd >= 0);
	
	b = buff_create(fd, BUFF_SZ);
	assert(b != NULL);

	c = buff_getc(b);
	assert(c == 'L');        
	assert(buff_ready(b));

	buff_ungetc(b, c);       
	assert(buff_ready(b));
	c = buff_getc(b);
	assert(c == 'L');

	res = buff_fgets(b, dest, sizeof dest);
	assert(res != NULL);
	assert(strcmp(dest, "Ligne1\n") == 0);

	res = buff_fgets_crlf(b, line_crlf, sizeof line_crlf);
	assert(res != NULL);
	assert(strcmp(line_crlf, "Ligne2\r\n") == 0);

	res = buff_fgets(b, dest, sizeof dest);
	assert(res != NULL);
	assert(strcmp(dest, "Fin") == 0);

	res = buff_fgets(b, dest, sizeof dest);
	assert(res == NULL);
	assert(buff_eof(b));

	
	buff_free(b);
	
	close(fd);
	
	remove(TEST_FILE);

	printf("Tout les tests ont été éffectué! \n");
	
	
	return 0;

}


void write_test_file(char * content) {
	
	FILE *f = fopen(TEST_FILE, "w");
	
	assert(f != NULL);
	
	fputs(content, f);
	
	
	fclose(f);
	
}


