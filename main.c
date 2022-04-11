#include "fonction.h"
#include "fonctions_de_base.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


int main(int argc, char *argv[]) 
{


	if(SDL_Init(SDL_INIT_VIDEO)){
		fprintf(stderr,"Erreur SDL : %s\n", SDL_GetError());
	}

	SDL_Surface *fenetre = NULL;
	SDL_Surface *sous_surface_plateau_de_jeu = NULL;

	SDL_Rect sous_surface_plateau_de_jeu_position;
	sous_surface_plateau_de_jeu_position.x=5;
	sous_surface_plateau_de_jeu_position.y=5;

	fenetre = SDL_SetVideoMode(500,500,32,SDL_HWSURFACE | SDL_RESIZABLE);
	SDL_WM_SetCaption("2048", NULL);
	SDL_FillRect(fenetre,NULL,SDL_MapRGB(fenetre->format,190,174,161));
	sous_surface_plateau_de_jeu=SDL_CreateRGBSurface(SDL_HWSURFACE,50,50,32,0,0,0,0);
	SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,128,128,128));
	int ligne = 0;
	int colonne = 0;
	for (ligne = 0 ; ligne < 4 ; ligne++){
		for (colonne = 0 ; colonne < 4 ; colonne++){
			sous_surface_plateau_de_jeu_position.x = (colonne*55)+5;
			SDL_BlitSurface(sous_surface_plateau_de_jeu,NULL,fenetre,&sous_surface_plateau_de_jeu_position);
		}	
		sous_surface_plateau_de_jeu_position.y+=55;
	}
	/* création de la police*/
	TTF_Init();
	TTF_Font *fontTest;
	fontTest = TTF_OpenFont("times-new-roman.ttf",30);
	SDL_Color fontColor = {0,0,0};


	SDL_Surface *nombre_de_la_case;
	SDL_Rect nombre_de_la_case_position;
	char nombre[4]="";
	nombre_de_la_case_position.x=30;
	nombre_de_la_case_position.y=30;

	
	clock_t time = clock();
	int plateau[4][4];
	int sauvegarde_plateau [4][4];
	int	score = 0 ;
	int meilleur_score=0;
	int sauvegarde_score = score;
	int exit = 0;

	FILE* fichier_de_sauvegarde = NULL;
	SDL_Event event;

	SDL_Flip(fenetre);

	while(exit == 0){
		time = clock();
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT){
			break;
		}
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.sym == SDLK_SPACE){
				initialisation_du_plateau(plateau, time,&score);
				sauvegarder_plateau_actuel(plateau,sauvegarde_plateau,&score,&sauvegarde_score);
				affichage_plateau (plateau,&score);
				fichier_de_sauvegarde = fopen("sauvegarde.txt", "r");
				if(fichier_de_sauvegarde != NULL){
					fseek(fichier_de_sauvegarde, 33, SEEK_SET); /* 33 est la position du meilleur score dans le fichier de sauvegarde*/
					fscanf(fichier_de_sauvegarde, "%d ", &meilleur_score);
					fclose(fichier_de_sauvegarde);
				}
				else {
					printf("Impossible de charger le meilleur score\n");
					exit = QUITTER;
				}
				printf("Le meilleur score est %d\n", meilleur_score);
			}
			else if (event.key.keysym.sym == SDLK_c){
				fichier_de_sauvegarde = fopen("sauvegarde.txt", "r");
				if(fichier_de_sauvegarde != NULL){
					int ligne = 0;
					int colonne = 0;
					for (ligne = 0 ; ligne < 4 ; ligne++){
						for (colonne = 0 ; colonne < 4 ; colonne ++){
							fscanf(fichier_de_sauvegarde, "%d ", plateau[ligne]+colonne);
						}
					}
					fscanf(fichier_de_sauvegarde, "%d ", &meilleur_score);
					fscanf(fichier_de_sauvegarde, "%d ", &score);
					fclose(fichier_de_sauvegarde);
				}
				else {
					printf("Impossible de charger la sauvegarde");
					exit = QUITTER;
				}
				affichage_plateau (plateau,&score);
				printf("Le meilleur score est %d\n", meilleur_score);
			}
			else if (event.key.keysym.sym == SDLK_RIGHT){
				sauvegarder_plateau_actuel(plateau,sauvegarde_plateau,&score,&sauvegarde_score);
				droite(plateau, time,&score);
				affichage_plateau (plateau,&score);
			}
			else if (event.key.keysym.sym == SDLK_LEFT){
				sauvegarder_plateau_actuel(plateau,sauvegarde_plateau,&score,&sauvegarde_score);
				gauche(plateau, time,&score);
				affichage_plateau (plateau,&score);
			}
			else if (event.key.keysym.sym == SDLK_DOWN){
				sauvegarder_plateau_actuel(plateau,sauvegarde_plateau,&score,&sauvegarde_score);
				bas(plateau, time,&score);
				affichage_plateau (plateau,&score);
			}
			else if (event.key.keysym.sym == SDLK_UP){
				sauvegarder_plateau_actuel(plateau,sauvegarde_plateau,&score,&sauvegarde_score);
				haut(plateau, time,&score);
				affichage_plateau (plateau,&score);
			}
			else if (event.key.keysym.sym == SDLK_r){
				restaurer_plateau_precedent(plateau,sauvegarde_plateau,&score,&sauvegarde_score);
				sauvegarder_plateau_actuel(plateau,sauvegarde_plateau,&score,&sauvegarde_score);
				affichage_plateau (plateau,&score);
			}
			else if (event.key.keysym.sym == SDLK_s){
				exit = QUITTER;
				fichier_de_sauvegarde = fopen("sauvegarde.txt", "w+");
				if(fichier_de_sauvegarde != NULL){
					int ligne = 0;
					int colonne = 0;
					for (ligne = 0 ; ligne < 4 ; ligne++){
						for (colonne = 0 ; colonne < 4 ; colonne ++){
							fprintf(fichier_de_sauvegarde, "%d ", plateau[ligne][colonne]);
						}
					}
					if(score>meilleur_score){
						printf("BRAVO!!!! Tu as fait le meilleur score, l'ancien meilleur score était de %d et le tiens est de %d !!!!!!\n",meilleur_score,score);
						meilleur_score=score;
					}
					fprintf(fichier_de_sauvegarde, "%d %d",meilleur_score,score);
					fclose(fichier_de_sauvegarde);
				}
				else {
					printf("Impossible de sauvegarder la partie .....");
				}
			}
			int ligne = 0;
			int colonne = 0;
			int cnt = 0;
			for (ligne = 0; ligne < 4; ligne++){
				for (colonne = 0 ; colonne < 4 ; colonne ++){
					if (plateau[ligne][colonne] != 0){
						sprintf(nombre,"%d",plateau[ligne][colonne]);
					}
					else {
						sprintf(nombre,"");
					}
					nombre_de_la_case=TTF_RenderText_Blended(fontTest,nombre,fontColor);
					if (plateau[ligne][colonne] != 0){
						while (plateau[ligne][colonne]/(pow(10,cnt)) >= 1){
							cnt+=1;
						}
						cnt-=1;

					}

					if (plateau[ligne][colonne] == 2){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,239,224,219));
					}
					else if (plateau[ligne][colonne] == 4){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,233,221,194));
					}
					else if (plateau[ligne][colonne] == 8){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,243,175,124));
					}
					else if (plateau[ligne][colonne] == 16){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,246,145,101));
					}
					else if (plateau[ligne][colonne] == 32){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,246,120,97));
					}
					else if (plateau[ligne][colonne] == 64){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,247,92,64));
					}
					else if (plateau[ligne][colonne] == 128){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,238,203,116));
					}
					else if (plateau[ligne][colonne] == 256){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,237,200,98));
					}
					else if (plateau[ligne][colonne] == 512){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,239,197,85));
					}
					else if (plateau[ligne][colonne] == 1024){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,238,192,66));
					}
					else if (plateau[ligne][colonne] == 2048){
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,238,188,49));
					}
					else{
						SDL_FillRect(sous_surface_plateau_de_jeu,NULL,SDL_MapRGB(fenetre->format,205,193,179));
					}
										



					sous_surface_plateau_de_jeu_position.y=(ligne*55)+5;
					sous_surface_plateau_de_jeu_position.x = (colonne*55)+5;
					nombre_de_la_case_position.x = sous_surface_plateau_de_jeu_position.x + ((sous_surface_plateau_de_jeu_position.w-14)/2)-8*cnt;
					nombre_de_la_case_position.y = sous_surface_plateau_de_jeu_position.y + ((sous_surface_plateau_de_jeu_position.h-34)/2);
					

					SDL_BlitSurface(sous_surface_plateau_de_jeu,NULL,fenetre,&sous_surface_plateau_de_jeu_position);
					SDL_BlitSurface(nombre_de_la_case,NULL,fenetre,&nombre_de_la_case_position);
					cnt = 0;
				}
			}

			SDL_Flip(fenetre);
		}
	}
	SDL_FreeSurface(fenetre);
	SDL_FreeSurface(sous_surface_plateau_de_jeu);
	SDL_Quit();
	return 0;
}
	