#include "fonctions_de_base.h"
#include "OperationPlateau.h"

void affichage_plateau (int tableau[TAILLE_PLATEAU][TAILLE_PLATEAU],int*score);
int demande_instruction(char *commande, int longueur_commande);
void test_affichage_plateau(void);
void test_demande_instruction(void);
int demande_instruction(char *commande, int longueur_commande);
void viderBuffer(void);
void print_ligne(int ligne[4]);
void test_echange(void);
void test_zeros_a_gauche();
void test_droite_ligne(void);
void test_droite(clock_t time,int*score);
void test_miroir_verticale(void);
int rdm_2_4(clock_t time);
void initialisation_du_plateau(int tab[4][4],clock_t time, int*score);
int exploration_du_plateau(int tab[4][4], int coordonnees[2],clock_t time);
void test_du_plateau(int tab[4][4],clock_t time);
void sauvegarder_plateau_actuel(int plateau_actuel[4][4],int plateau_precedent[4][4], int* score_actuel, int* sauvegarde_score);
void restaurer_plateau_precedent(int plateau_actuel[4][4],int plateau_precedent[4][4], int* score_actuel, int* score_precedent);
int VerificationMouvementPossible (int plateau[TAILLE_PLATEAU][TAILLE_PLATEAU], int coordonnees[2],clock_t time);
int droite_ligne (int ligne[4],int*score);



