#include<stdlib.h>
#include<stdio.h>
#include"partie.h"


int main(){
    int choix;
    int choixx;
	char fichier[20];
    printf("******ECHECS******\n\n");
    printf("[1]: Nouvelle Partie\n");
    printf("[2]: Partie Charger\n");
    scanf("%d",&choix);
    if(choix==1){
        partie_jouer(partie_nouvelle());
    }
    else{
		printf("[1]: Jouer \n");
        printf("[2]: Animation\n");
        scanf("%d",&choixx);
        if(choixx==1){
            printf("Entrez le nom du fichier a charger : ");
            scanf("%s",fichier);
            partie_jouer(partie_charger(fichier));
        }
        else{
            printf("Entrez le nom du fichier a charger : ");
            scanf("%s",fichier);
            replay_jouer(replay_charger(fichier));
        }
    }
    return EXIT_SUCCESS;
}






