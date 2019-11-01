#include"listecj.h"
#include<stdlib.h>

maillonCJ_t * maillon_creer(coup_t c){
    maillonCJ_t * res=malloc(sizeof(maillonCJ_t));
    res->coup=c;
    res->suivant=NULL;
    res->precedent=NULL;
    return res;
}

void maillon_detruire(maillonCJ_t * m){
    free(m);
}

listeCJ_t * liste_initialiser(){
    listeCJ_t * res=malloc(sizeof(listeCJ_t));
    res->premier=NULL;
    res->dernier=NULL;
    res->taille=0;
    return res;
}

int liste_vide(listeCJ_t * l){
    if(!l->taille)
        return 1;
    return 0;
}
void liste_detruire(listeCJ_t * l){
    while(!liste_vide(l))
        maillon_detruire(liste_extraire_fin(l));
    free(l);
}

void liste_ajouter_fin(listeCJ_t * l,coup_t p){
    maillonCJ_t * nvo=maillon_creer(p);
    if(liste_vide(l))
        l->premier=nvo;
    else{
        nvo->precedent=l->dernier;
        l->dernier->suivant=nvo;
    }
    l->dernier=nvo;
    l->taille++;
}

maillonCJ_t * liste_extraire_debut(listeCJ_t * l){
    maillonCJ_t * res=l->premier;
    if(!liste_vide(l)){
        l->premier=res->suivant;
        res->suivant=NULL;
        l->taille--;
        if(liste_vide(l))
            l->dernier=NULL;
        else
            l->premier->precedent=NULL;
    }
    return res;
}

maillonCJ_t * liste_extraire_fin(listeCJ_t * l){
    maillonCJ_t * res=l->dernier;
    if(!liste_vide(l)){
        l->dernier=res->precedent;
        res->precedent=NULL;
        l->taille--;
        if(liste_vide(l))
            l->premier=NULL;
        else
            l->dernier->suivant=NULL;
    }
    return res;
}

coup_t extraire_coup_fin(listeCJ_t * l){
    maillonCJ_t * m=liste_extraire_fin(l);
    coup_t res=m->coup;
    maillon_detruire(m);
    return res;
}

coup_t extraire_coup_debut(listeCJ_t * l){
    maillonCJ_t * m=liste_extraire_debut(l);
    coup_t res=m->coup;
    maillon_detruire(m);
    return res;
}
