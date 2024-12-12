all: polynome.o main_polynome.o
	gcc polynome.o main_polynome.o -o prog_polynome

polynome.o: polynome.c polynome.h
	gcc -c -Wall -pedantic -std=c99 polynome.c

main_polynome.o: main_polynome.c polynome.h
	gcc -c -Wall -pedantic -std=c99 main_polynome.c

clean:
	rm *.o prog_polynome
