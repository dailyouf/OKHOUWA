all: list.o main.o
	gcc list.o main.o -o exec -lncurses 
	

list.o: list.c list.h item.h
	gcc -c -Wall -pedantic -std=c99 list.c

main.o: main.c list.c list.h item.h
	gcc -c -Wall -pedantic -std=c99 main.c

clean:
	rm *.o exec
