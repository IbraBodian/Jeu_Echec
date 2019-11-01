#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include <unistd.h>
#include"partie.h"


int case_vide(partie_t * partie,coordonnee_t c){
    if(piece_caractere(partie->echiquier[c.x][c.y])=='.')
        return 1;
    return 0;
}

void modifier_case(partie_t * partie,piece_t p,coordonnee_t c){
    partie->echiquier[c.x][c.y]=p;
}

void changer_joueur(partie_t * partie){
    if(partie->joueur==NOIR)
        partie->joueur=BLANC;
	else
    	partie->joueur=NOIR;
}

void afficher_echiquier(partie_t * partie){
    int i;
    int j;
    int k=0;
	printf("        NOIRS     \n");
    for(i=0;i<8;i++){/*affiche 0 1 2 3 4 5 6 7*/
        if(i==0)
            printf("   %d",i);
        else
            printf(" %d",i);
   }
    printf("\n");
    for(j=0;j<8;j++){
        printf("%d  ",k);/*affiche 0 1 2 3 4 5 6 7*/
        for(i=0;i<8;i++){
           piece_afficher(partie->echiquier[j][i]);
           printf(" ");
        }
        printf("\n");
        k++;
    }
	printf("        BLANCS     \n");
}

void deplacement(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    if(case_vide(partie,arrivee)){
        modifier_case(partie,partie->echiquier[depart.x][depart.y],arrivee);
        liste_ajouter_fin(partie->lcj,creer_coup(depart,arrivee,NON));
    }
	else{
    	empiler(partie->lpc,partie->echiquier[arrivee.x][arrivee.y]);
        modifier_case(partie,partie->echiquier[depart.x][depart.y],arrivee);
        liste_ajouter_fin(partie->lcj,creer_coup(depart,arrivee,OUI));
	}
    partie->echiquier[depart.x][depart.y]=piece_identifier('.');
    changer_joueur(partie);
}

void annuler_deplacement(partie_t * partie){
	coup_t c=extraire_coup_fin(partie->lcj);
	changer_joueur(partie);
    partie->echiquier[c.depart.x][c.depart.y]=partie->echiquier[c.arrivee.x][c.arrivee.y];
    if(c.capture==OUI)
        partie->echiquier[c.arrivee.x][c.arrivee.y]=depiler(partie->lpc);
    else
        partie->echiquier[c.arrivee.x][c.arrivee.y]=piece_identifier('.');
}

coordonnee_t saisie_case(){
    coordonnee_t res;
    do{
    printf("ordonnee ");
    scanf("%d",&res.x);
    printf("abscisse ");
    scanf("%d",&res.y);
	if(res.x<0||res.x>7||res.y<0||res.y>7)
		printf("\ncase inexistante!\n\n");
    }while(res.x<0||res.x>7||res.y<0||res.y>7);
    return res;
}

partie_t * partie_creer(){
    partie_t * res=malloc(sizeof(partie_t));
    res->lpc=pile_initialiser();
    res->lcj=liste_initialiser();
    res->joueur=BLANC;
    return res;
}

void partie_detruire(partie_t * partie){
    pile_detruire(partie->lpc);
    liste_detruire(partie->lcj);
    free(partie);
}

partie_t * partie_charger(char * fichier){
    char plateau[8][8];
    int i,j;
    char format1[3];
    FILE * f=NULL;
    partie_t * res=partie_creer();
    if((f=fopen(fichier,"r"))!=NULL){
        format1[0]=fgetc(f);
    	format1[1]=fgetc(f);
    	fgetc(f);
        if((format1[0]!='P')||(format1[1]!='L'))
            return NULL;
        else{
            for(i=0;i<8;i++){
                for(j=0;j<8;j++)
                    plateau[i][j]=fgetc(f);
                fgetc(f);
            }
        }
        fclose(f);
    }
    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            res->echiquier[i][j]=piece_identifier(plateau[i][j]);
    return res;
}

partie_t * replay_charger(char * fichier){
    int a,b,c,d;
    coup_t coup;
    coordonnee_t depart,arrivee;
    char format1[3];
    FILE * f=NULL;
    partie_t * res=partie_nouvelle();
    if((f=fopen(fichier,"r"))!=NULL){
        format1[0]=fgetc(f);
    	format1[1]=fgetc(f);
    	fgetc(f);
        if((format1[0]!='P')||(format1[1]!='R'))
            return NULL;
        else{
            while(!feof(f)){
                fscanf(f,"%d %d %d %d",&a,&b,&c,&d);
                depart=creer_coordonnee(a,b);
                arrivee=creer_coordonnee(c,d);
                coup=creer_coup(depart,arrivee,0);
                liste_ajouter_fin(res->lcj,coup);
            }
        }
        fclose(f);
    }
    return res;
}

void replay_jouer(partie_t * partie){
    int i;
    int taille=partie->lcj->taille;
    coup_t c;
    for(i=0;i<taille;i++){
        afficher_echiquier(partie);
        c=extraire_coup_debut(partie->lcj);
        deplacement(partie,c.depart,c.arrivee);
        sleep(5000);
    }
}

void partie_sauvegarder(partie_t * partie,char * fichier){
    int i,j;
    FILE * f=NULL;
    if((f=fopen(fichier,"w"))!=NULL){
        fprintf(f,"PL");
        fprintf(f,"\n");
        for(i=0;i<8;i++){
            for(j=0;j<8;j++)
                fprintf(f,"%c",piece_caractere(partie->echiquier[i][j]));
            fprintf(f,"\n");
        }
    fclose(f);
    }
}

void coup_sauvegarder(partie_t * partie,char * fichier){
    int i;
    coup_t c;
    FILE * f=NULL;
    int taille=partie->lcj->taille;
    if((f=fopen(fichier,"w"))!=NULL){
        fprintf(f,"PR");
        fprintf(f,"\n");
        for(i=0;i<taille;i++){
            c=extraire_coup_debut(partie->lcj);
            fprintf(f,"%d %d",c.depart.x,c.depart.y);
            fprintf(f," %d %d\n",c.arrivee.x,c.arrivee.y);
        }
    fclose(f);
    }
}

partie_t * partie_nouvelle(){
    int i,j;
    partie_t * res=partie_creer();
    char piecen[9]="TCFREFCT";
    char pieceb[9]="tcfrefct";
    for(i=0;i<8;i++)
        res->echiquier[0][i]=piece_creer(NOIR,piecen[i]);
    for(i=0;i<8;i++)
        res->echiquier[1][i]=piece_creer(NOIR,'P');
    for(i=2;i<6;i++)
        for(j=0;j<8;j++)
            res->echiquier[i][j]=piece_creer(2,'.');
    for(i=0;i<8;i++)
        res->echiquier[6][i]=piece_creer(BLANC,'p');
    for(i=0;i<8;i++)
        res->echiquier[7][i]=piece_creer(BLANC,pieceb[i]);
    return res;
}

void partie_jouer(partie_t * partie){
    coordonnee_t depart;
    coordonnee_t arrivee;
    int jouer=1;
    int choix;
    int quit;
	char sauvegarde[20];
	char coup[20];
    afficher_echiquier(partie);
    while(jouer){
        printf("******MENU******\n");
        if(partie->joueur==NOIR)
            printf("Au tour des noirs\n");
        else
            printf("Au tour des blancs\n");
        printf("quelle option choisissez-vous ?\n");
        printf("[1]: Jouer\n");
        printf("[2]: Annuler deplacement\n");
        printf("[3]: Quitter le jeu \n");
        scanf("%d",&choix);
        if(choix==1){
            do{
                printf("ENTREZ LA COORDONNEE DE DEPART : ");
                depart=saisie_case();
                printf("ENTREZ LA COORDONNEE D'ARRIVEE : ");
                arrivee=saisie_case();
				if(!deplacement_valide(partie,depart,arrivee))
					printf("\ndeplacement impossible, reesayez !\n\n");
            }while(!deplacement_valide(partie,depart,arrivee));
            deplacement(partie,depart,arrivee);
            afficher_echiquier(partie);
        }
        if(choix==2){
            annuler_deplacement(partie);
            afficher_echiquier(partie);
        }
        if(choix==3)
            jouer=0;
    }
    printf("Voulez-vous sauvegarder la partie ?\n");
    printf("[1]: OUI\n");
    printf("[2]: NON\n");
    scanf("%d",&quit);
    if(quit==1){
		printf("nommez la sauvegarde de l'echiquier au format *.plt : ");
		scanf("%s",sauvegarde);
        partie_sauvegarder(partie,sauvegarde);
        printf("nommez la sauvegarde des coups au format *.part : ");
        scanf("%s",coup);
        coup_sauvegarder(partie,coup);
	}
}

int deplacement_valide(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    if(case_vide(partie,depart))
        return 0;
    if(partie->joueur==BLANC){
        if(piece_couleur(partie->echiquier[depart.x][depart.y])==NOIR)
            return 0;
        return verification_type_blanc(partie,depart,arrivee);
    }
    if(partie->joueur==NOIR){
        if(piece_couleur(partie->echiquier[depart.x][depart.y])==BLANC)
            return 0;
        return verification_type_noir(partie,depart,arrivee);
    }
	return 0;
}


int verification_type_blanc(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    if(islower(piece_caractere(partie->echiquier[arrivee.x][arrivee.y])))
        return 0;
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='p')
        return deplacement_valide_pion(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='t')
        return deplacement_valide_tour(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='c')
        return deplacement_valide_cavalier(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='f')
        return deplacement_valide_fou(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='r')
        return deplacement_valide_roi(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='e')
        return deplacement_valide_reine(partie,depart,arrivee);
	return 0;
}

int verification_type_noir(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    if(isupper(piece_caractere(partie->echiquier[arrivee.x][arrivee.y])))
        return 0;
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='P')
        return deplacement_valide_pion(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='T')
        return deplacement_valide_tour(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='C')
        return deplacement_valide_cavalier(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='F')
        return deplacement_valide_fou(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='R')
        return deplacement_valide_roi(partie,depart,arrivee);
    if(piece_caractere(partie->echiquier[depart.x][depart.y])=='E')
        return deplacement_valide_reine(partie,depart,arrivee);
	return 0;
}

int deplacement_valide_pion(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    if(piece_couleur(partie->echiquier[depart.x][depart.y])==NOIR){
        if((arrivee.y==depart.y)&&(arrivee.x==depart.x+1))
            if(case_vide(partie,arrivee))
                return 1;
        if(depart.x==1)
            if((arrivee.y==depart.y)&&(arrivee.x==depart.x+2))
                if((case_vide(partie,arrivee))&&(case_vide(partie,creer_coordonnee(depart.x+1,depart.y))))
                    return 1;
        if((arrivee.x==depart.x+1)&&((arrivee.y==depart.y-1)||(arrivee.y==depart.y+1)))
           if(!case_vide(partie,arrivee))
                return 1;
    }
    else
        if((arrivee.y==depart.y)&&(arrivee.x==depart.x-1))
            if(case_vide(partie,arrivee))
                return 1;
        if(depart.x==6)
            if((arrivee.y==depart.y)&&(arrivee.x==depart.x-2))
                if((case_vide(partie,arrivee))&&(case_vide(partie,creer_coordonnee(depart.x-1,depart.y))))
                    return 1;
        if((arrivee.x==depart.x-1)&&((arrivee.y==depart.y-1)||(arrivee.y==depart.y+1)))
           if(!case_vide(partie,arrivee))
                return 1;

    return 0;
}

int deplacement_valide_tour(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    int i;
    if(arrivee.x==depart.x){
        if(arrivee.y>depart.y){
            for(i=1;i<arrivee.y-depart.y;i++)
                if(!case_vide(partie,creer_coordonnee(depart.x,depart.y+i)))
                    return 0;
            return 1;
        }
        else{
            for(i=1;i<depart.y-arrivee.y;i++)
                if(!case_vide(partie,creer_coordonnee(depart.x,arrivee.y+i)))
                    return 0;
            return 1;
        }
    }
    if(arrivee.y==depart.y){
        if(arrivee.x>depart.x){
           for(i=1;i<arrivee.x-depart.x;i++)
                if(!case_vide(partie,creer_coordonnee(depart.x+i,depart.y)))
                    return 0;
            return 1;
        }
        else{
            for(i=1;i<depart.x-arrivee.x;i++)
                if(!case_vide(partie,creer_coordonnee(arrivee.x+i,depart.y)))
                    return 0;
            return 1;
        }
    }
    return 0;
}

int deplacement_valide_fou(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    int i;
    if((abs(depart.x-arrivee.x))==(abs(depart.y-arrivee.y)))
        if((depart.x>arrivee.x)&&(depart.y>arrivee.y)){
            for(i=1;i<depart.x-arrivee.x;i++)
                if(!case_vide(partie,creer_coordonnee(depart.x-i,depart.y-i)))
                    return 0;
            return 1;
        }
        if((depart.x>arrivee.x)&&(depart.y<arrivee.y)){
             for(i=1;i<depart.x-arrivee.x;i++)
                if(!case_vide(partie,creer_coordonnee(depart.x-i,depart.y+i)))
                    return 0;
            return 1;
        }
        if((depart.x<arrivee.x)&&(depart.y>arrivee.y)){
            for(i=1;i<depart.x-arrivee.x;i++)
                if(!case_vide(partie,creer_coordonnee(depart.x+i,depart.y-i)))
                    return 0;
            return 1;
        }
        if((depart.x<arrivee.x)&&(depart.y<arrivee.y)){
            for(i=1;i<depart.x-arrivee.x;i++)
                if(!case_vide(partie,creer_coordonnee(depart.x+i,depart.y+i)))
                    return 0;
            return 1;
        }
    return 0;
}

int deplacement_valide_cavalier(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    if((abs(depart.x-arrivee.x)==2)&&(abs(depart.y-arrivee.y)==1))
        return 1;
    if((abs(depart.x-arrivee.x)==1)&&(abs(depart.y-arrivee.y)==2))
        return 1;
    return 0;
}

int deplacement_valide_roi(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    int i,j;
    for(i=-1;i<2;i++)
        for(j=-1;i<2;j++)
            if((arrivee.x==depart.x+i)&&(arrivee.y==depart.y+j))
                return 1;
    return 0;
}

int deplacement_valide_reine(partie_t * partie,coordonnee_t depart,coordonnee_t arrivee){
    if((deplacement_valide_fou(partie,depart,arrivee))||(deplacement_valide_tour(partie,depart,arrivee)))
        return 1;
    return 0;
}
