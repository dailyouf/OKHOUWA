#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TEST_FILE "test.txt"

void write_test_file(const char *content) {
    FILE *f = fopen(TEST_FILE, "w");
    assert(f != NULL);
    fputs(content, f);
    fclose(f);
}

int main(void) {

    // 1. Prepare test data
    const char *lines = "Line1\nLine2\r\nEnd";
    write_test_file(lines);

    // 2. Open file and create buffer
    FILE *f = fopen(TEST_FILE, "r");
    assert(f != NULL);
    int fd = fileno(f);
    buffer *b = buff_create(fd, 8);
    assert(b != NULL);

    // 3. Test buff_getc and buff_ready
    int c = buff_getc(b);
    assert(c == 'L');
    assert(buff_ready(b));

    // 4. Test buff_ungetc
    buff_ungetc(b, c);
    assert(buff_ready(b));
    c = buff_getc(b);
    assert(c == 'L');

    // 5. Read first line with buff_fgets
    char dest[32];
    char *res = buff_fgets(b, dest, sizeof dest);
    assert(res != NULL);
    assert(strcmp(dest, "Line1\n") == 0);

    // 6. Read second line with buff_fgets_crlf
    res = buff_fgets_crlf(b, dest, sizeof dest);
    assert(res != NULL);
    assert(strcmp(dest, "Line2\r\n") == 0);

    // 7. Read remainder: "End"
    res = buff_fgets(b, dest, sizeof dest);
    assert(res != NULL);
    assert(strcmp(dest, "End") == 0);

    // 8. EOF behavior
    res = buff_fgets(b, dest, sizeof dest);
    assert(res == NULL);
    assert(buff_eof(b));

    // 9. Cleanup
    buff_free(b);
    fclose(f);
    remove(TEST_FILE);

    printf("All tests passed!\n");
    
    
    return 0;
}

