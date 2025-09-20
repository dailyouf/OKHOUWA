#ifndef _ITEM_H
#define _ITEM_H

typedef float item;

#define F_value 0.0

#define key(A) (A)
#define assign(A, B) { A = B; }
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (!less(A, B) && !less(B, A))
#define exch(A, B) { item tmp = A; A = B; B = tmp; }
#define display(A) { printf("%6.2f ", key(A)); }
#define destroy(A)

#endif
