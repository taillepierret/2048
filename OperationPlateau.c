#include "OperationPlateau.h"




void echange (int*A, int*B){
	int temp = *B;
	*B = *A;
	*A = temp;
}


int zeros_a_gauche_une_ligne(int ligne[4]){
	/* cette focntion decale les elements nuls d'une ligne à gauche et renvoie 1 si un mouvement à ete effectue et 0 sinon*/
	int mvt_effectue = 0;
	int i = 0;

	int colonne = 0;
	for ( i=0 ; i<4 ; i++){
		for (colonne=3 ; colonne>0 ; colonne--){
			if (ligne[colonne] == 0 && ligne[colonne-1] != 0 ){
				echange(ligne+colonne,ligne+colonne-1);
				mvt_effectue = 1;
			}
		}
	}
return mvt_effectue;
}


void miroir_verticale_ligne(int ligne[4]){
	echange(ligne+3,ligne);
	echange(ligne+1,ligne+2);
}

void miroir_verticale(int tab[4][4]){
	int ligne = 0;
	for ( ligne=0 ; ligne<4 ; ligne++ ){
		miroir_verticale_ligne(tab[ligne]);
	}
}

void gauche(int tab[4][4],clock_t time,int*score){
	miroir_verticale(tab);
	droite(tab, time,score);
	miroir_verticale(tab);
}

void miroir_diagonale(int tab[4][4]){
	int i = 0;
	for ( i=1 ; i<4 ; i++ ){
		echange(tab[0]+i, tab[i]);
	}
	for ( i=1 ; i<3 ; i++){
		echange(tab[3]+i, tab[i]+3);
	}
	echange(tab[1]+2, tab[2]+1);
}

void bas(int tab[4][4],clock_t time,int*score){
	miroir_diagonale(tab);
	droite(tab, time,score);
	miroir_diagonale(tab);
}

void haut(int tab[4][4],clock_t time,int*score){
	miroir_diagonale(tab);
	gauche(tab, time,score);
	miroir_diagonale(tab);
}