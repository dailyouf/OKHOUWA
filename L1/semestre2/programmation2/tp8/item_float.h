#ifndef _ITEM_FLOAT_H
#define _ITEM_FLOAT_H

#include <stdio.h>

typedef float item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (key(A) == key(B))
#define exch(A, B) { item tmp = A; A = B; B = tmp; }
#define display(A) { printf("%5.3f ", key(A)); }
#define destroy(A)

#endif
