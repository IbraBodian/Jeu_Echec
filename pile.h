#ifndef PILE_H
#define PILE_H
#include"listepc.h"


typedef listePC_t pile_t;



pile_t * pile_initialiser();
int pile_vide(pile_t * p);
void empiler(pile_t * l,piece_t p);
piece_t depiler(pile_t * p);
void pile_detruire(pile_t * p);


#endif
