#include "fonction.h"

char* message_erreur_champs_trop_long = "\n\n############################################################\nATTENTION, la commande est trop longue !\n############################################################\n\n";
int tab_proba[4] = {2,2,2,4};



int aleatoire_0_a_999(clock_t time){
	return time%1000 ;
}


int rdm_2_4(clock_t time){
	int rdm_2_ou_4;
	int rdm = aleatoire_0_a_999(time)%4; /*renvoie un entier entre 0 et 3*/
	rdm_2_ou_4 = tab_proba[rdm];
	return rdm_2_ou_4;
}


void affichage_plateau (int tableau[TAILLE_PLATEAU][TAILLE_PLATEAU],int*score){
	int ligne = 0;
	int colonne = 0;
	for (ligne=0 ; ligne<TAILLE_PLATEAU ; ligne++ ){
		for (colonne=0 ; colonne<TAILLE_PLATEAU ; colonne++ ){
			printf("%d    ", tableau[ligne][colonne]);
		}
		printf("\n");
	}
	printf("score: %d\n",*score);
}



void viderBuffer(){
	int c = 0;
	while ( c!= '\n' && c!= EOF){
		c = getchar();
	}
}




int demande_instruction(char *commande, int longueur_commande){
	char *positionEntree = NULL;

	if (fgets(commande, longueur_commande, stdin) != NULL){
		positionEntree = strchr(commande, '\n');
		if (positionEntree != NULL){
			*positionEntree = '\0';
		}
		else{
			viderBuffer();
			printf("%s",message_erreur_champs_trop_long);
		}
		return 1;
	}
	else{
		viderBuffer();
		return 0;
	}

}




void print_ligne(int ligne[4]){
	int i = 0;
	for ( i=0 ; i<4 ; i++){
		printf("%d",ligne[i]);
	}
	printf("\n");
}


int exploration_du_plateau(int tab[4][4], int coordonnees[2],clock_t time){
	/* cette fonction va donner dans un tableau un couple de coordonnees dont 
	la case possède un 0 de manière uniforme (si mon rdm_2_4 est uniforme).
	la fonction renvoie 0  si elle trouve au minimum une case avec un 0
	____________________1  si elle trouve une case qui vaut 2048
	____________________-1 pour tous les autres cas*/
	int nb_cases_avec_0 = 0;
	int tab_coordonnees_cases_avec_0[16][2];
	int ligne = 0;
	int colonne = 0;
	for (ligne=0 ; ligne<4 ; ligne++){
		for (colonne=0 ; colonne<4 ; colonne++){
			if (tab[ligne][colonne] == 2048){
			/* verification des cases pour voir si nous avons effectue 2048*/
				return 1;
			}
			else if (tab[ligne][colonne] == 0){
				tab_coordonnees_cases_avec_0[nb_cases_avec_0][0]=ligne;
				tab_coordonnees_cases_avec_0[nb_cases_avec_0][1]=colonne;
				nb_cases_avec_0 +=1;
			}
		}
	}
	if (nb_cases_avec_0 == 0){
		return -1;
	}
	int coord[2];
	int num_case_sans_0_rdm = aleatoire_0_a_999(time)%nb_cases_avec_0;
	coord[0] = tab_coordonnees_cases_avec_0[num_case_sans_0_rdm ][0];
	coord[1] = tab_coordonnees_cases_avec_0[num_case_sans_0_rdm ][1];
	*coordonnees = coord[0];
	*(coordonnees+1) = coord[1];
	return 0;
}

void test_du_plateau(int tab[4][4],clock_t time){
	int coord[2];
	int temp = exploration_du_plateau(tab, coord, time);
	if (temp == 1){
		printf("vs avez gagne !!!\n");
	}

	else if(temp == -1){
		printf("ATTENTION là c'est chaud il n'y a plus de case avec des 0\n");
	}

	else if (temp == 0){
		printf("vs pouvez encore jouer\n");
	}
}



int droite_ligne (int ligne[4], int*score){
	/* cette focntion decale les elements non-nuls d'une ligne à droite et renvoie 1 si un mouvement à ete effectue et 0 sinon*/
	int colonne;
	int mvt_effectue1 = 0;
	int mvt_effectue2 = 0;
	mvt_effectue2=zeros_a_gauche_une_ligne(ligne);
	for (colonne=3 ; colonne>0 ; colonne--){
		if (ligne[colonne]==ligne[colonne-1] && ligne[colonne-1] != 0){
			*(ligne+colonne)=ligne[colonne]+ligne[colonne-1];
			*score += ligne[colonne];
			*(ligne+colonne-1)=0;
			mvt_effectue1 = 1;
		}
	}
	mvt_effectue2 |= zeros_a_gauche_une_ligne(ligne);
	return mvt_effectue1 || mvt_effectue2 ;
}

void droite(int tab[4][4],clock_t time,int*score){
	int ligne = 0;
	int mvt_effectue = 0;
	for ( ligne=0 ; ligne<4 ; ligne++ ){
		mvt_effectue += droite_ligne(tab[ligne],score);
	}
	int coord[2];
	if (mvt_effectue > 0){
		exploration_du_plateau(tab, coord, time);
		*(tab[coord[0]]+coord[1])=rdm_2_4(time);
	}
}





void initialisation_du_plateau(int tab[4][4],clock_t time, int*score){
	int ligne = 0;
	int colonne = 0;
	for (ligne=0 ; ligne<4 ; ligne++){
		for (colonne=0 ; colonne<4 ; colonne++){
			tab[ligne][colonne]=0;
		}
	}
	int coord[2];
	exploration_du_plateau(tab, coord, time);
	*(tab[coord[0]]+coord[1])=rdm_2_4(time);
	exploration_du_plateau(tab, coord, time);
	*(tab[coord[0]]+coord[1])=rdm_2_4(time);
	*score=0;

}

void sauvegarder_plateau_actuel(int plateau_actuel[4][4],int sauvegarde_plateau[4][4], int* score_actuel, int* sauvegarde_score){
	int ligne = 0;
	int colonne = 0;
	for (ligne = 0 ; ligne < 4 ; ligne ++){
		for (colonne = 0 ; colonne < 4 ; colonne ++){
			*(sauvegarde_plateau[ligne]+colonne) = plateau_actuel[ligne][colonne];
		}
	}
	*sauvegarde_score=*score_actuel;
}

void restaurer_plateau_precedent(int plateau_actuel[4][4],int plateau_precedent[4][4], int* score_actuel, int* score_precedent){
	int ligne = 0;
	int colonne = 0;
	for (ligne = 0 ; ligne < 4 ; ligne ++){
		for (colonne = 0 ; colonne < 4 ; colonne ++){
			*(plateau_actuel[ligne]+colonne) = plateau_precedent[ligne][colonne];
		}
	}
	*score_actuel=*score_precedent;
}

int Verification0SurLePlateau (int plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int coordonnees[2],clock_t time){
	/* Cette fonction permet de chercher les 0 sur le plateau. Si la recherche aboutie, la fonction renvoie 0 avec le couple de coordonnées (en parametres) sinon elle renvoie 1.*/
	int nb_cases_avec_0 = 0;
	int tab_coordonnees_cases_avec_0[16][2];
	int ligne = 0;
	int colonne = 0;
	for (ligne=0 ; ligne<4 ; ligne++){
		for (colonne=0 ; colonne<4 ; colonne++){
			if (plateau[ligne][colonne] == 0){
				tab_coordonnees_cases_avec_0[nb_cases_avec_0][0]=ligne;
				tab_coordonnees_cases_avec_0[nb_cases_avec_0][1]=colonne;
				nb_cases_avec_0 +=1;
			}
		}
	}
	if (nb_cases_avec_0 == 0){
		return 1;
	}
	int coord[2];
	int num_case_sans_0_rdm = aleatoire_0_a_999(time)%nb_cases_avec_0;
	coord[0] = tab_coordonnees_cases_avec_0[num_case_sans_0_rdm ][0];
	coord[1] = tab_coordonnees_cases_avec_0[num_case_sans_0_rdm ][1];
	*coordonnees = coord[0];
	*(coordonnees+1) = coord[1];
	return 0;
}

int VerificationMouvementPossible (int plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int coordonnees[2],clock_t time){
	/* Cette fonction permet de verifier qu'aucun mouvement n'est possible en regardant s'il y a encore des 0 sur le plateau puis en regardant si des nombres côte a côte sont identiques. 
	Elle renvoie 0 si aucun mouvement n'est possible sinon elle renvoie 1.*/
	if (Verification0SurLePlateau (plateau, coordonnees, time)){
		return 0;
	}

	int ligne = 0;
	int colonne = 0;
	for (ligne = 0 ; ligne < TAILLE_PLATEAU ; ligne ++){
		for (colonne = 0 ; colonne < TAILLE_PLATEAU-1 ; colonne ++){
			if (plateau[ligne][colonne] == plateau[ligne][colonne+1]){
				return 1;
			}
		}
	}

	miroir_diagonale(plateau);

	ligne = 0;
	colonne = 0;
	for (ligne = 0 ; ligne < TAILLE_PLATEAU ; ligne ++){
		for (colonne = 0 ; colonne < TAILLE_PLATEAU-1 ; colonne ++){
			if (plateau[ligne][colonne] == plateau[ligne][colonne+1]){
				miroir_diagonale(plateau);
				return 1;
			}
		}
	}
	miroir_diagonale(plateau);
	return 0;
}

