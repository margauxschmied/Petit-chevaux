#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"
#include <time.h>
#include<windows.h>




int main() {
	
	int menu;
	printf("voulez-vous: \ncommencer une parti(1) \nquitter le jeu(2) \n");
	scanf_s("%d",&menu);
	if (menu == 1) {
		Joueur groupe[4];
		int i = 0;
		int d;

		
		int nbparticipant;
		nbparticipant = init_jeu(&groupe);

		plateau();

		while (groupe[0].gagnant != 1 || groupe[1].gagnant != 1 || groupe[2].gagnant != 1 || groupe[3].gagnant != 1) {
			for (int i = 0; i < nbparticipant; i++) {
				int recommence = 0;
				printf("joueur %d pour lancer le dé touché n'importe quelle touche \n", i + 1);
				system("pause");
				d = de();
				printf("le joueur %d a eu %d au lance du de \n", i + 1, d);
				

				if (groupe[i].actif == 1) {

					if (d == 6 && groupe[i].chactif>0) {
						int choix;
						
						recommence = 1;
						if (groupe[i].ordi == 1 && groupe[i].chactif<4) {
							choix = 1;
							commence(&groupe, i, d);
						}
						else { 
							if(groupe[i].chactif < 4){
								printf("voulez-vous sortir(1) un cheval ou avancer(2): ");
								scanf_s("%d", &choix);
								while (choix != 1 && choix != 2) {
									printf("veuillez choisir une valeur convenable");
									scanf_s("%d", &choix);
								}
								if (choix == 1) {
									commence(&groupe, i, d);
								}
								else {
									deplacement(&groupe, i, d, nbparticipant);
									
								}
							}
							else {
								printf("le joueur %d ne peux que avance \n", i + 1);
								deplacement(&groupe, i, d, nbparticipant);
								
							}
						}
					}

					if (recommence == 1) {
						d = de();
						printf("le joueur %d a eu %d au lance du de \n", i + 1, d);
						recommence == 0;
					}
					
					if (groupe[i].gagnant ==0) {
						deplacement(&groupe, i, d, nbparticipant);
					}

					for (int j = 0; j < groupe[i].chactif; j++) {
						if (groupe[i].ecurie[j].echelle == 8) {
							printf("le joueur %d a gagne avec le cheval numero %d \n", i + 1, j + 1);
							return 0;
						}
					}
				}
				if (groupe[i].actif == 0) {
					commence(&groupe, i, d);
				}

			}
		}
	}
	else {
		return 0;
	}
	system("pause");
	return 0;
}