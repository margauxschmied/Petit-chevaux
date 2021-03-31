#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include <time.h>
#include<windows.h>

int init_jeu(Joueur* groupe) {
	int nbjoueur = 0;
	int nbordi = 0;
	printf("nombre de joueur (0 a 4): ");
	scanf_s("%d", &nbjoueur);
	if (nbjoueur > 4) {
		printf("le nombre de joueur est trop grand il y en aura donc 4 \n");
		nbjoueur = 4;
	}
	else {
		printf("nombre d'ordinateur voulue (0 a %d): ",4-nbjoueur);
		scanf_s("%d", &nbordi);
		if (nbjoueur + nbordi > 4) {
			nbordi = 4 - nbjoueur;
			printf("nombre d'ordinateur trop grand il n'y aura que %d ordinateur \n", nbordi);
		}
	}

	for (int i = 0; i < nbjoueur; i++) {
		/*groupe[i].pseudo = malloc(sizeof(char) * 50);  //    ne marche pas
		printf("pseudo du joueur %d: ", i + 1);
		scanf_s("%s", &groupe[i].pseudo);
		printf("le joueur s'appel %s ", groupe[i].pseudo);*/
		groupe[i].ordi = 0;
		groupe[i].actif = 0;
		groupe[i].chactif = 0;
		groupe[i].gagnant = 0;
		for (int k = 0; k < 4; k++) {
			groupe[i].ecurie[k].depart = 1+(i*14);
			groupe[i].ecurie[k].echelle = 0;
			groupe[i].ecurie[k].emplacement = 0;
			groupe[i].ecurie[k].tour = 0;
		}
		
	}
	for (int j = nbjoueur; j < (nbjoueur + nbordi); j++) {
		//groupe[j].pseudo = malloc(sizeof(char) * 50);
		//groupe[j].pseudo = "ordi";
		groupe[j].ordi = 1;
		groupe[j].actif = 0;
		groupe[j].chactif = 0;
		groupe[j].gagnant = 0;
		for (int k = 0; k < 4; k++) {
			groupe[j].ecurie[k].depart = 1+(j*14);
			groupe[j].ecurie[k].echelle = 0;
			groupe[j].ecurie[k].emplacement = 0;
			groupe[j].ecurie[k].tour = 0;
		}
	}
	printf("le jeu est initialise \n");
	return nbordi + nbjoueur;
}

int de() {
	srand(time(NULL));   //viens de stack overflow
	int d = (rand() % 6) + 1;
	Sleep(900);
	return d;
}

void commence(Joueur* groupe, int i, int d) {
	if (d == 6) {
		groupe[i].actif = 1;
		groupe[i].ecurie[groupe[i].chactif].emplacement = groupe[i].ecurie[groupe[i].chactif].depart;
		groupe[i].chactif += 1;
		printf("le joueur %d sort le cheval %d \n", i+1, groupe[i].chactif);
		
	}
}

/*void manger(Joueur* groupe, int i, int j, int nbparticipant) {
	if (groupe[i].ecurie[j].echelle == 0) {
		for (int l = 0; l < nbparticipant; l++) {
			for (int k = 0; k < 4; k++) {
				if (groupe[i].ecurie[j].emplacement == groupe[l].ecurie[k].emplacement && groupe[l].ecurie[k].echelle == 0) {
					groupe[l].chactif -= 1;
					int a = groupe[l].ecurie[k].emplacement;
					for (int m = k; m < 3; m++) {
						groupe[l].ecurie[k] = groupe[l].ecurie[k + 1];
					}
					groupe[l].ecurie[3].emplacement = groupe[l].ecurie[k].depart;
					groupe[l].ecurie[3].tour = 0;
				}
			}
		}
	}
}*/


void deplacement(Joueur* groupe, int i, int d, int nbparticipant) {
	if (groupe[i].actif == 1) {
		if (groupe[i].ordi == 1) {
			for (int j = 0; j < groupe[i].chactif; j++) {

				if (i == 0) {
					if (groupe[i].ecurie[j].emplacement + d == 56 || groupe[i].ecurie[j].echelle >= 1) {
						groupe[i].ecurie[j].emplacement = 56;
						if (groupe[i].ecurie[j].echelle==0) {
							groupe[i].ecurie[j].echelle = 1;
						}
						if (groupe[i].ecurie[j].echelle == d || groupe[i].ecurie[j].echelle == 7 && d == 6) { // si le de vaut la prochaine marche alors il monte
							groupe[i].ecurie[j].echelle += 1;
						}
						break;
					}			

					if (groupe[i].ecurie[j].emplacement + d < 56 && groupe[i].ecurie[j].emplacement + d != groupe[i].ecurie[0].emplacement && groupe[i].ecurie[j].emplacement + d != groupe[i].ecurie[1].emplacement && groupe[i].ecurie[j].emplacement + d != groupe[i].ecurie[2].emplacement && groupe[i].ecurie[j].emplacement + d != groupe[i].ecurie[3].emplacement) {
						groupe[i].ecurie[j].emplacement += d;
						break;
					}

					int recule = ((groupe[i].ecurie[j].emplacement + d) % 56);

					if (groupe[i].ecurie[j].emplacement + d > 56 && 56 - recule != groupe[i].ecurie[0].emplacement && 56 - recule + d != groupe[i].ecurie[1].emplacement && 56 - recule != groupe[i].ecurie[2].emplacement && 56 - recule != groupe[i].ecurie[3].emplacement) {
						groupe[i].ecurie[j].emplacement = 56 - recule;
						break;
					}

				}

				else {
					if (groupe[i].ecurie[j].emplacement + d > 56 && groupe[i].ecurie[j].tour == 0 && (groupe[i].ecurie[j].emplacement + d)%56 != groupe[i].ecurie[0].emplacement && (groupe[i].ecurie[j].emplacement + d) % 56 != groupe[i].ecurie[1].emplacement && (groupe[i].ecurie[j].emplacement + d) % 56 != groupe[i].ecurie[2].emplacement && (groupe[i].ecurie[j].emplacement + d) % 56 != groupe[i].ecurie[3].emplacement) {
						groupe[i].ecurie[j].tour = 1;
						groupe[i].ecurie[j].emplacement = (groupe[i].ecurie[j].emplacement + d) % 56;
						printf("le joueur %d a fait un tour \n", i + 1);
						break;
					}

					if (groupe[i].ecurie[j].emplacement + d == groupe[i].ecurie[j].depart - 1 || groupe[i].ecurie[j].echelle >= 1) {
						groupe[i].ecurie[j].emplacement += d;

						if (groupe[i].ecurie[j].echelle == 0) {
							groupe[i].ecurie[j].echelle = 1;
						}
						if (groupe[i].ecurie[j].echelle == d || groupe[i].ecurie[j].echelle == 7 && d == 6) { // si le de vaut laprochaine marche alors il monte
							groupe[i].ecurie[j].echelle += 1;
						}
						break;
					}

					int recule = ((groupe[i].ecurie[j].emplacement + d) % (groupe[i].ecurie[j].depart - 1));

					if (groupe[i].ecurie[j].emplacement + d > groupe[i].ecurie[j].depart - 1 && groupe[i].ecurie[j].tour == 1 && groupe[i].ecurie[j].depart - recule != groupe[i].ecurie[0].emplacement && groupe[i].ecurie[j].depart - recule != groupe[i].ecurie[1].emplacement && groupe[i].ecurie[j].depart - recule != groupe[i].ecurie[2].emplacement && groupe[i].ecurie[j].depart - recule != groupe[i].ecurie[3].emplacement) {
						groupe[i].ecurie[j].emplacement = groupe[i].ecurie[j].depart - recule;
						break;

					}

					else {
						if (groupe[i].ecurie[j].emplacement += d != groupe[i].ecurie[0].emplacement && groupe[i].ecurie[j].emplacement + d != groupe[i].ecurie[1].emplacement && groupe[i].ecurie[j].emplacement + d != groupe[i].ecurie[2].emplacement && groupe[i].ecurie[j].emplacement + d != groupe[i].ecurie[3].emplacement) {
							groupe[i].ecurie[j].emplacement += d;
							break;
						}
					}

				}
				//manger(&groupe, i, j, nbparticipant);
				//plateau(&groupe, i, j);
			}
		}
		else {
			int c = 1;
			int done = 0;

			if (groupe[i].chactif >= 1) {
				printf("quel cheval voulez-vous bouger? ");
				scanf_s("%d", &c);
				while (c != 1 && c != 2 && c != 3 && c != 4 || c > groupe[i].chactif) {
					printf("veuillez choisir une nombre convenable ");
					scanf_s("%d", &c);
				}
			}
			if (i == 0) {
				if (done==0 && groupe[i].ecurie[c - 1].emplacement + d == 56 || groupe[i].ecurie[c - 1].echelle >= 1) {
					groupe[i].ecurie[c - 1].emplacement = 56;
					if (groupe[i].ecurie[c - 1].echelle == 0) {
						groupe[i].ecurie[c - 1].echelle = 1;
					}
					if (groupe[i].ecurie[c - 1].echelle == d || groupe[i].ecurie[c - 1].echelle == 7 && d == 6) { // si le de vaut la prochaine marche alors il monte
						groupe[i].ecurie[c - 1].echelle += 1;
					}
					done = 1;
				}
				else {

					int recule = ((groupe[i].ecurie[c - 1].emplacement + d) % 56);

					if (done==0 && groupe[i].ecurie[c - 1].emplacement + d > 56) {
						groupe[i].ecurie[c - 1].emplacement = 56 - recule;
						done = 1;
					}

					else {
						groupe[i].ecurie[c - 1].emplacement += d;

					}

				}
			}

			else {
				if (done==0 && groupe[i].ecurie[c - 1].emplacement + d > 56 && groupe[i].ecurie[c - 1].tour == 0) {
					groupe[i].ecurie[c - 1].tour = 1;
					groupe[i].ecurie[c - 1].emplacement = (groupe[i].ecurie[c - 1].emplacement + d) % 56;
					printf("le joueur %d a fait un tour \n", i + 1);
					done = 1;
				}
				else {
					if (done==0 && groupe[i].ecurie[c - 1].emplacement + d == groupe[i].ecurie[c - 1].depart - 1 || groupe[i].ecurie[c - 1].echelle >= 1) {
						groupe[i].ecurie[c - 1].emplacement += d;

						if (groupe[i].ecurie[c - 1].echelle == 0) {
							groupe[i].ecurie[c - 1].echelle = 1;
						}
						if (groupe[i].ecurie[c - 1].echelle == d || groupe[i].ecurie[c - 1].echelle == 7 && d == 6) { // si le de vaut laprochaine marche alors il monte
							groupe[i].ecurie[c - 1].echelle += 1;
						}

						done = 1;
					}

					else {
						int recule = ((groupe[i].ecurie[c - 1].emplacement + d) % (groupe[i].ecurie[c - 1].depart - 1));

						if (done==0 && groupe[i].ecurie[c - 1].emplacement + d > groupe[i].ecurie[c - 1].depart - 1 && groupe[i].ecurie[c - 1].tour == 1) {
							groupe[i].ecurie[c - 1].emplacement = (groupe[i].ecurie[c - 1].depart - 1) - recule;
							done = 1;
						}

						else {
							groupe[i].ecurie[c - 1].emplacement += d;
						}
					}
				}
			}
			//manger(&groupe, i, c - 1, nbparticipant);
			//plateau(&groupe, i, c-1);
		}
	}

	
		
	for (int j = 0; j < 4; j++) {
		if (groupe[i].ecurie[j].echelle == 8) {
			printf("le cheval %d du joueur %d a atteint la coupe \n", j + 1, i + 1);
			groupe[i].gagnant = 1;
		}
		else {
			if (groupe[i].ecurie[j].echelle > 0) {
				printf("le cheval %d du joueur %d est a la marche %d de l'echelle \n", j + 1, i + 1, groupe[i].ecurie[j].echelle - 1);
			}
			else {
				if (groupe[i].ecurie[j].emplacement == 0) {
					printf("le cheval %d du joueur %d est a l'ecurie \n", j + 1, i + 1);
				}
				else {
					printf("le cheval %d du joueur %d est a la case %d \n", j + 1, i + 1, groupe[i].ecurie[j].emplacement);
				}
			}
		}
	}	
}

void plateau() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (i > 0 && i < 14 && i != 7 && j != 7 && j != 0 && j != 14) {
				printf("   ");
			}
			else {
				if (i == 7 && j == 7) {
					printf("[c]");
				}
				else {
					if (i == 1 && j == 7 || i == 13 && j == 7 || i == 7 && j == 1 || i == 7 && j == 13) {
						printf("[1]");
					}
					else {
						if (i == 2 && j == 7 || i == 12 && j == 7 || i == 7 && j == 2 || i == 7 && j == 12) {
							printf("[2]");
						}
						else {
							if (i == 3 && j == 7 || i == 11 && j == 7 || i == 7 && j == 3 || i == 7 && j == 11) {
								printf("[3]");
							}
							else {
								if (i == 4 && j == 7 || i == 10 && j == 7 || i == 7 && j == 4 || i == 7 && j == 10) {
									printf("[4]");
								}
								else {
									if (i == 5 && j == 7 || i == 9 && j == 7 || i == 7 && j == 5 || i == 7 && j == 9) {
										printf("[5]");
									}
									else {
										if (i == 6 && j == 7 || i == 8 && j == 7 || i == 7 && j == 6 || i == 7 && j == 8) {
											printf("[6]");
										}
										else {
											printf("[ ]");
										}
									}
								}
							}
						}
					}
				}
			}
		}
		printf("\n");
	}
}







