tp7: tp7.o bst.o binary_tree.o queue_link.o stack_link.o
	gcc -o tp7 tp7.o bst.o binary_tree.o queue_link.o stack_link.o

tp7.o: tp7.c bst.h binary_tree.h BT.h item.h queue_link.h stack_link.h
	gcc -c tp7.c
	
bst.o: bst.c bst.h binary_tree.h BT.h item.h
	gcc -c bst.c	
	
binary_tree.o: binary_tree.c binary_tree.h BT.h item.h
	gcc -c binary_tree.c

queue_link.o: queue_link.c queue_link.h
	gcc -c queue_link.c

stack_link.o: stack_link.c stack_link.h
	gcc -c stack_link.c

clean:
	rm -f *.o tp4

