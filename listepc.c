#include"listepc.h"
#include<stdlib.h>

maillonPC_t * creer_maillon(piece_t p){
    maillonPC_t * res=malloc(sizeof(maillonPC_t));
    res->piece=p;
    res->suivant=NULL;
    return res;
}

void detruire_maillon(maillonPC_t * m){
    free(m);
}

listePC_t * initialiser_liste(){
    listePC_t * res=malloc(sizeof(listePC_t));
    res->premier=NULL;
    res->dernier=NULL;
    res->taille=0;
    return res;
}

int vide_liste(listePC_t * l){
    if(!l->taille)
        return 1;
    return 0;
}

void detruire_liste(listePC_t * l){
    while(!vide_liste(l))
        detruire_maillon(extraire_liste_debut(l));
    free(l);
}

void liste_ajouter_debut(listePC_t * l,piece_t p){
    maillonPC_t * nvo=creer_maillon(p);
    if(vide_liste(l))
        l->dernier=nvo;
    else
        nvo->suivant=l->premier;
    l->premier=nvo;
    l->taille++;
}

maillonPC_t * extraire_liste_debut(listePC_t * l){
    maillonPC_t * res=NULL;
    if(!vide_liste(l)){
       res=l->premier;
       l->premier=res->suivant;
       res->suivant=NULL;
       l->taille--;
    if(vide_liste(l))
        l->dernier=NULL;
    }
    return res;
}
