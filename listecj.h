#ifndef LISTECJ_H
#define LISTECJ_H
#include"coup.h"


struct maillonCJ_s{
    coup_t coup;
    struct maillonCJ_s * suivant;
    struct maillonCJ_s * precedent;
};
typedef struct maillonCJ_s maillonCJ_t;

struct listeCJ_s{
	struct maillonCJ_s * premier;
	struct maillonCJ_s * dernier;
	int taille;
};
typedef struct listeCJ_s listeCJ_t;


maillonCJ_t * maillon_creer(coup_t c);
void maillon_detruire(maillonCJ_t * m);
listeCJ_t * liste_initialiser();
int liste_vide(listeCJ_t * l);
void liste_detruire(listeCJ_t * l);
void liste_ajouter_fin(listeCJ_t * l,coup_t p);
maillonCJ_t * liste_extraire_debut(listeCJ_t * l);
maillonCJ_t * liste_extraire_fin(listeCJ_t * l);
coup_t extraire_coup_fin(listeCJ_t * l);
coup_t extraire_coup_debut(listeCJ_t * l);


#endif
