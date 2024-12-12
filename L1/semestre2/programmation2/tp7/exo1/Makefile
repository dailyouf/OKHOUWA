all: date.o individu.o laureat.o main_turing.o
	gcc date.o individu.o laureat.o main_turing.o -o exec
	
date.o: date.c date.h
	gcc -c -Wall -ansi date.c
	
individu.o: individu.c individu.h date.h
	gcc -c -Wall -ansi individu.c
	
laureat.o: laureat2.c laureat.h individu.h date.h 
	gcc -c -Wall -ansi laureat2.c
	
main_turing.o: main_turing.c laureat.h individu.h date.h
	gcc -c -Wall -ansi main_turing.c
