#ifndef COUP_H
#define COUP_H
#include"coordonnee.h"
#define OUI 1
#define NON 0


struct coup_s{
	coordonnee_t depart;
	coordonnee_t arrivee;
	short int capture;
};
typedef struct coup_s coup_t;

coup_t creer_coup(coordonnee_t d, coordonnee_t a,short int cap);


#endif
