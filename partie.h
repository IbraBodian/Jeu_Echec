#ifndef PARTIE_H
#define PARTIE_H
#include"pile.h"
#include"listecj.h"


struct partie_s{
    piece_t echiquier[8][8];
    pile_t * lpc;
    listeCJ_t * lcj;
    short int joueur;
};
typedef struct partie_s partie_t;


int case_vide(partie_t * partie,coordonnee_t c);
void modifier_case(partie_t * partie,piece_t p,coordonnee_t c);
void changer_joueur(partie_t * partie);
void afficher_echiquier(partie_t * partie);
void deplacement(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);
void annuler_deplacement(partie_t * partie);
coordonnee_t saisie_case();
partie_t * partie_creer();
void partie_detruire(partie_t * partie);
void partie_sauvegarder(partie_t * partie,char * fichier);
partie_t * partie_charger(char * fichier);
partie_t * partie_nouvelle();
void partie_jouer(partie_t * partie);
void coup_sauvegarder(partie_t * partie,char * fichier);
partie_t * replay_charger(char * fichier);
void replay_jouer(partie_t * partie);


int deplacement_valide(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);
int verification_type_blanc(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);
int verification_type_noir(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);
int deplacement_valide_pion(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);
int deplacement_valide_tour(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);
int deplacement_valide_cavalier(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);
int deplacement_valide_fou(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);
int deplacement_valide_roi(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);
int deplacement_valide_reine(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee);


#endif

