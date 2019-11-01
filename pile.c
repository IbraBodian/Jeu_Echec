#include"pile.h"

pile_t * pile_initialiser(){
    return initialiser_liste();
}

void empiler(pile_t * l,piece_t p){
    liste_ajouter_debut(l,p);
}

piece_t depiler(pile_t * p){
    maillonPC_t * m=extraire_liste_debut(p);
    piece_t res=m->piece;
    detruire_maillon(m);
    return res;
}

void pile_detruire(pile_t * p){
    detruire_liste(p);
}

int pile_vide(pile_t * p){
    return vide_liste(p);
}
