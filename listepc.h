#ifndef LISTEPC_H
#define LISTEPC_H
#include"piece.h"


struct maillonPC_s{
	piece_t piece;
	struct maillonPC_s * suivant;
};
typedef struct maillonPC_s maillonPC_t;

struct listePC_s{
	struct maillonPC_s * premier;
	struct maillonPC_s * dernier;
	int taille;
};
typedef struct listePC_s listePC_t;

maillonPC_t * creer_maillon(piece_t p);
void detruire_maillon(maillonPC_t * m);
listePC_t * initialiser_liste();
int vide_liste(listePC_t * l);
void detruire_liste(listePC_t * l);
void liste_ajouter_debut(listePC_t * l,piece_t p);
maillonPC_t * extraire_liste_debut(listePC_t * l);


#endif

