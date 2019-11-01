#include"coup.h"

coup_t creer_coup(coordonnee_t d, coordonnee_t a,short int cap){
    coup_t coup;
    coup.depart=d;
    coup.arrivee=a;
    coup.capture=cap;
    return coup;
}
