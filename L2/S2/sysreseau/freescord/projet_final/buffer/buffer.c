/* Youcef GHEDAMSI 12302243
Je déclare qu'il s'agit de mon propre travail.
Ce travail a été réalisé intégralement par un être humain. */

#include "buffer.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

struct buffer {
	int fd;
	size_t buffsz;
	int i; // fait référence à l'indice où on est arrivé dans la lecture / écriture sur le buffer
	char * data;
	size_t a_data; // données disponibles à la lecture
	int eof;
};

struct buffer * buff_create(int fd, size_t buffsz) {

	
	struct buffer * buf = malloc(sizeof(struct buffer));
	
	buf->fd = fd;
	
	buf->buffsz = buffsz;
	
	buf->i = 0;
	
	buf->eof = 0;
	
	buf->data = malloc(buf->buffsz * sizeof(char));
	
	buf->a_data = 0;
	
	return buf;
}

int buff_getc(buffer *b) {

	
	if (b->eof == 1)
		return -1;
	
	if (b->i < b->a_data) 
		return b->data[b->i++];
	
	b->i = 0;	
	
	if ((b->a_data = read(b->fd, b->data, b->buffsz)) < 0)
		return -1;
	
	if (b->a_data == 0) {
		b->eof = 1;
		return -1;
	}

	return 	b->data[b->i++];
	
}

int buff_ungetc(buffer *b, int c) {
	
	if (b->i == 0)
		return -1;
	
	b->data[--b->i] = c;
	
	return c; 
}

void buff_free(buffer *b) {
	
	free(b->data);

	free(b);
}

int buff_eof(const buffer *buff) {
	
	return buff->eof;
	
}

int buff_ready(const buffer *buff) {
	
	if (buff->i < buff->a_data)
		return 1;
	
	return 0;
}

char *buff_fgets(buffer *b, char *dest, size_t size) {
	
	char c = '\0';
	int n = 0;
			
	if (size == 0)
		return NULL;			
	
	do {
		c = buff_getc(b);
		dest[n++] = c; 
			
	} while (c != '\n' && c != EOF && n+1 < size);
			
	if ((c == EOF) || (n==0))
		return NULL;
			
	dest[n] = '\0';
	
	return dest;
}

char *buff_fgets_crlf(buffer *b, char *dest, size_t size) {
	
	char c = '\0';
	int n = 0;
	char last_c;
	
	if (size == 0)
		return NULL;
	
	do {
		last_c = c;
		c = buff_getc(b);
		dest[n++] = c;
			
	} while ((c != '\n' || last_c != '\r') && c != EOF && n+1 < size);
	
	if ((c == EOF) || (n==0))
		return NULL;
			
	dest[n] = buff_getc(b);
	
	return dest;
}
