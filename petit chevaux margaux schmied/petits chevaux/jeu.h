struct cheval {
	int depart;
	int echelle;     /*le cheval est-il sortie de l'écurie?*/
	int emplacement;   /* numéro de la case ou ce trouve de cheval*/
	int tour;
} ;

typedef struct cheval Cheval;

struct joueur  {
	char *pseudo;
	int ordi;
	int actif; /*le joueur est-il un ordinateur?*/
	int chactif; /* nombre de chevaux sorti de l'ecurie*/
	Cheval ecurie[4];
	int gagnant;
};

typedef struct joueur Joueur;


int init_jeu(Joueur* groupe);

int de();

void commence(Joueur* groupe, int i, int d);

int manger(Joueur* groupe, int i, int j, int nbparticipant);

void deplacement(Joueur* groupe, int i, int d, int nbparticipant);


