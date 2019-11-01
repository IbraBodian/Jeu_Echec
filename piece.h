#ifndef PIECE_H
#define PIECE_H
#define BLANC 1
#define NOIR 0


struct piece_s{
    int couleur;
    char type;
};
typedef struct piece_s piece_t;


piece_t piece_creer (int c,char t);
int piece_couleur (piece_t p);
piece_t piece_identifier (char c);
char piece_caractere(piece_t p);
void piece_afficher (piece_t p);


#endif
