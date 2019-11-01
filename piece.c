#include<stdio.h>
#include<ctype.h>
#include"piece.h"


piece_t piece_creer (int c,char t){
    piece_t piece;
    piece.couleur=c;
    piece.type=t;
    return piece;
}


int piece_couleur(piece_t p){
    return p.couleur;
}


piece_t piece_identifier(char c){
    piece_t piece;
	piece.type=c;
	if(isupper(c))                 /*Si c'est une lettre majuscule ,la couleur de la piece est noire*/
		piece.couleur=NOIR;
	if(islower(c))                 /*Si c'est une lettre minuscule,la couleur de la piece  est blanche*/
		piece.couleur=BLANC;
	if(c=='.')
		piece.couleur=2;           /*couleur par defaut,pour la case vide*/
    return piece;
}


char piece_caractere(piece_t p){
    return p.type;
}


void piece_afficher(piece_t p){
    printf("%c",p.type);
}
