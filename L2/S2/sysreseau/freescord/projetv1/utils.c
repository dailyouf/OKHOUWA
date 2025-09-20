#include <string.h>


char *crlf_to_lf(char *line_with_crlf) {

	int l = strlen(line_with_crlf);
	
	line_with_crlf[l-2] = '\n';
	line_with_crlf[l-1] = '\0';
	
	return line_with_crlf;	
	
}

char *lf_to_crlf(char *line_with_lf) {

	int l = strlen(line_with_lf);
	
	line_with_lf[l-1] = '\r';
	line_with_lf[l] = '\n';
	line_with_lf[l+1] = '\0';
	
	return line_with_lf;	
	
}
