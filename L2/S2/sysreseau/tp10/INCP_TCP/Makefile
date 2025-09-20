CC=gcc
CFLAGS=-Wall -Wfatal-errors -Wpointer-arith -g
LDFLAGS=-Wall -g -pthread
OBJS=client_tcp_incp.o serveur_tcp_incp.o

all: client serveur

client: client_tcp_incp.o
	$(CC) $(LDFLAGS) client_tcp_incp.o -o $@
serveur: serveur_tcp_incp.o
	$(CC) $(LDFLAGS) serveur_tcp_incp.o -o $@
client_tcp_incp.o: client_tcp_incp.c
serveur_tcp_incp.o: serveur_tcp_incp.c

.PHONY: clean
clean:
	rm -f client serveur $(OBJS)
