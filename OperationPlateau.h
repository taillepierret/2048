#include "fonctions_de_base.h"

void droite(int tab[4][4],clock_t time,int*score);
void miroir_verticale_ligne(int ligne[4]);
void miroir_verticale(int tab[4][4]);
void miroir_diagonale(int tab[4][4]);
void gauche(int tab[4][4],clock_t time,int*score);
void haut(int tab[4][4],clock_t time,int*score);
void bas(int tab[4][4],clock_t time,int*score);
int zeros_a_gauche_une_ligne(int ligne[4]); 