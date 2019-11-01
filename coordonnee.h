#ifndef COORDONNEE_H
#define COORDONNEE_H


struct coordonnee_s{
	int x;
	int y;
};
typedef struct coordonnee_s coordonnee_t;

coordonnee_t creer_coordonnee(int x,int y);


#endif
