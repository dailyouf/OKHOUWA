#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "tp12-1.h"


int add1odd(char *fname) {
	
	int fd, value;
	
	if ((fd = open(fname, O_RDWR)) == -1) {
		return -1;
	}
	
	while (read(fd, &value, sizeof(int)) > 0) {
		if ((value % 2) == 1) {
			value++;
			lseek(fd, -sizeof(int), SEEK_CUR);
			write(fd, &value, sizeof(int));
		}
	}
	
	close(fd);
	
	return;
}
