CFLAGS=-g -Wall -ansi -pedantic -O3
FICHIERS=partie.o pile.o listepc.o listecj.o coup.o coordonnee.o piece.o main.o

all:$(FICHIERS)
	gcc $(CFLAGS) $(FICHIERS) -o programme
partie.o:partie.c
	gcc -c $(CFLAGS) partie.c
pile.o:pile.c
	gcc -c $(CFLAGS) pile.c
listepc.o:listepc.c
	gcc -c $(CFLAGS) listepc.c
listecj.o:listecj.c
	gcc -c $(CFLAGS) listecj.c
coup.o:coup.c
	gcc -c $(CFLAGS) coup.c
coordonnee.o:coordonnee.c
	gcc -c $(CFLAGS) coordonnee.c
piece.o:piece.c
	gcc -c $(CFLAGS) piece.c
main.o:main.c
	gcc -c $(CFLAGS) main.c
