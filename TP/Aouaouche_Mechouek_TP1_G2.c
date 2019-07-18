#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define LONG 800
#define LARGE 600

#include "TP_BIBLIO.h"
#include "conio2.h"
#include "conio.h"


void SDL_Graphique(void);

int main(int argc, char **argv)
{
    SDL_Graphique();
    system("color F0");
    srand(time(NULL));
    ChoixMenu();
    return EXIT_SUCCESS;
}

void SDL_Graphique(void)
{

    ///************************* VARIABLES, CREATION FENETRE + AJOUT ICONE *************************
    //ShowWindow (GetConsoleWindow(), SW_HIDE);  //Cacher console
    SDL_Window *fenetre=NULL;
    SDL_Renderer *pers_mario=NULL;
    SDL_Surface *icone=NULL;
    int x=0;

    if(SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    fenetre=SDL_CreateWindow("******** WELCOME TO OLYMPIC GAMES ********", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, LONG, LARGE,0);
    if(fenetre==NULL)
    {
        SDL_Log("ERREUR LORS DE LA CREATION DE LA FENETRE > %s\n",SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    icone=SDL_LoadBMP("./SDL/Images/icone.bmp");
    SDL_SetWindowIcon(fenetre,icone);

    ///******************************************************************************************

    ///******************************* AJOUT DE L'IMAGE D'ARRIERE PLAN **************************
    SDL_Surface *Fond=SDL_LoadBMP("./SDL/Images/fond_mario.bmp");
    SDL_Rect pos_fond;

    pos_fond.x=0;
    pos_fond.y=0;

    SDL_BlitSurface(Fond,NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
    SDL_UpdateWindowSurface(fenetre);


    /// **********************************************MARIO PERSONNAGE********************************************
    pers_mario=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_SOFTWARE);

    if(pers_mario==NULL)
    {
        exit(EXIT_FAILURE);
    }

    SDL_Surface *S_mario[4]={SDL_LoadBMP("./SDL/Sprites/mario.bmp"),
                             SDL_LoadBMP("./SDL/Sprites/mario1.bmp"),
                             SDL_LoadBMP("./SDL/Sprites/mario2.bmp"),
                             SDL_LoadBMP("./SDL/Sprites/mario3.bmp")};
    SDL_Texture *mario[4]={SDL_CreateTextureFromSurface(pers_mario,S_mario[0]),
                            SDL_CreateTextureFromSurface(pers_mario,S_mario[1]),
                             SDL_CreateTextureFromSurface(pers_mario,S_mario[2]),
                              SDL_CreateTextureFromSurface(pers_mario,S_mario[3])},
                *CurrentMario=mario[0];

    SDL_FreeSurface(S_mario[0]); SDL_FreeSurface(S_mario[1]); SDL_FreeSurface(S_mario[2]), SDL_FreeSurface(S_mario[3]);


    SDL_Rect pos_mario;
    pos_mario.x=128; pos_mario.y=458;

    SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
    SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
    SDL_RenderPresent(pers_mario);

    ///********************************************************LOGO ESI****************************************************************
    SDL_Surface *esi=SDL_LoadBMP("./SDL/Images/esi.bmp");
    SDL_Rect pos_esi;

    pos_esi.x=730;
    pos_esi.y=5;

    SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
    SDL_UpdateWindowSurface(fenetre);

    ///**************************************************SUPPORT OLYMPIQUE**************************************************************
    SDL_Surface *support=SDL_LoadBMP("./SDL/Sprites/support.bmp");

    SDL_Rect pos_support;

    pos_support.x=645;
    pos_support.y=487;

    SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
    SDL_UpdateWindowSurface(fenetre);

    ///**************************************************FLAMME OLYMPIQUE***************************************************************
    SDL_Surface *flamme=SDL_LoadBMP("./SDL/Sprites/feu.bmp");

    SDL_Rect pos_flamme;

    pos_flamme.x=650;
    pos_flamme.y=426;

    ///**************************************************BOULE DE FEU********************************************************************
    SDL_Surface *boule_feu=SDL_LoadBMP("./SDL/Sprites/fireball.bmp");

    SDL_Rect pos_boule_feu;

    pos_boule_feu.x=432;
    pos_boule_feu.y=480;


    ///**************************************************BIENVENUE*******************************************************************
    SDL_Surface *welcome=SDL_LoadBMP("./SDL/Images/bienvenue.bmp");

    SDL_Rect pos_welcome;

    pos_welcome.x=150;
    pos_welcome.y=30;
    ///*************************************************MUSIQUE***********************************************************************
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *mario_song;
    mario_song=Mix_LoadMUS("./SDL/Sons/mario_fond.mp3");
    Mix_PlayMusic(mario_song, 5);

    ///**************************************************AFFICHAGE ECRITURE**************************************************************
    TTF_Init();
    TTF_Font *police=NULL;
    police = TTF_OpenFont("./SDL/mariofont.ttf",19);

    if(police==NULL)
        {
           SDL_Log("Impossible de charger la police > %s\n",SDL_GetError());
           exit(EXIT_FAILURE);
        }

    SDL_Color couleur_noire = {0,0,0};
    SDL_Color couleur_rouge= {255,143,53};
    SDL_Surface *texte, *info;
    SDL_Rect pos_texte, pos_info;

    pos_texte.x=10; pos_texte.y=30;
    pos_info.x=10; pos_info.y=60;

    texte=TTF_RenderText_Blended(police, "Appuyez sur la touche fleche pour avancer ...", couleur_noire);
    info=TTF_RenderText_Blended(police, "Activez le son pour une meilleure experience !", couleur_rouge);

    SDL_BlitSurface(texte,NULL, SDL_GetWindowSurface(fenetre),&pos_texte);
    SDL_BlitSurface(info,NULL, SDL_GetWindowSurface(fenetre),&pos_info);
    SDL_UpdateWindowSurface(fenetre);

    ///***********************************************GESTION DES EVENEMENTS*******************************************************
    SDL_bool boucle_infinie=SDL_TRUE;

    while(boucle_infinie)
    {
        SDL_Event evenement; //Variable de type événement

        while(SDL_PollEvent(&evenement)) //Fonction qui capture tous les événements
        {
            switch(evenement.type)
            {
                case SDL_KEYDOWN:
                    switch(evenement.key.keysym.sym)
                    {
                        case SDLK_RIGHT:

                            if(pos_mario.x<400)
                            {
                                if(CurrentMario==mario[0])
                                {
                                    SDL_RenderClear(pers_mario);
                                    SDL_BlitSurface(Fond,NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                    SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                    SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                    SDL_UpdateWindowSurface(fenetre);
                                    CurrentMario=mario[1];
                                    pos_mario.x=pos_mario.x+3;
                                    SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                    SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                    SDL_RenderPresent(pers_mario);
                                }

                                if(CurrentMario==mario[1])
                                {
                                    SDL_RenderClear(pers_mario);
                                    SDL_BlitSurface(Fond,NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                    SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                    SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                    SDL_UpdateWindowSurface(fenetre);
                                    CurrentMario=mario[2];
                                    pos_mario.x=pos_mario.x+3;
                                    SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                    SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                    SDL_RenderPresent(pers_mario);
                                }

                                if(CurrentMario==mario[2])
                                {
                                    SDL_RenderClear(pers_mario);
                                    SDL_BlitSurface(Fond,NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                    SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                    SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                    SDL_UpdateWindowSurface(fenetre);
                                    CurrentMario=mario[3];
                                    pos_mario.x=pos_mario.x+3;
                                    SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                    SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                    SDL_RenderPresent(pers_mario);
                                }

                                if(CurrentMario==mario[3])
                                {
                                    SDL_RenderClear(pers_mario);
                                    SDL_BlitSurface(Fond,NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                    SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                    SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                    SDL_UpdateWindowSurface(fenetre);
                                    CurrentMario=mario[0];
                                    pos_mario.x=pos_mario.x+3;
                                    SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                    SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                    SDL_RenderPresent(pers_mario);
                                }
                            }
                            else
                            {
                                   if(x!=1)
                                   {
                                   police = TTF_OpenFont("./SDL/mariofont.ttf",19);

                                    if(police==NULL)
                                    {
                                        SDL_Log("Impossible de charger la police > %s\n",SDL_GetError());
                                        exit(EXIT_FAILURE);
                                    }


                                    texte=TTF_RenderText_Blended(police, "Appuyez sur la touche Espace...", couleur_noire);

                                    SDL_BlitSurface(texte,NULL, SDL_GetWindowSurface(fenetre),&pos_texte);
                                    SDL_UpdateWindowSurface(fenetre);
                                    x=1;
                                   }


                            }
                        continue;


                        case SDLK_SPACE:
                            if(pos_mario.x>=400)
                            {
                                Mix_HaltMusic();
                                mario_song=Mix_LoadMUS("./SDL/Sons/spect1.mp3");
                                Mix_PlayMusic(mario_song, 1);
                                SDL_BlitSurface(boule_feu,NULL, SDL_GetWindowSurface(fenetre),&pos_boule_feu);
                                SDL_UpdateWindowSurface(fenetre);

                                while(pos_boule_feu.x<720)
                                    {
                                        pos_boule_feu.x=pos_boule_feu.x+2;
                                        SDL_BlitSurface(Fond, NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                        SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                        SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                        SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                        SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                        SDL_RenderPresent(pers_mario);
                                        SDL_BlitSurface(boule_feu,NULL, SDL_GetWindowSurface(fenetre),&pos_boule_feu);
                                        SDL_UpdateWindowSurface(fenetre);

                                    }

                                Mix_HaltMusic();
                                mario_song=Mix_LoadMUS("./SDL/Sons/spect2.mp3");
                                Mix_PlayMusic(mario_song, 5);
                                SDL_BlitSurface(Fond, NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                SDL_RenderPresent(pers_mario);
                                SDL_BlitSurface(flamme,NULL, SDL_GetWindowSurface(fenetre),&pos_flamme);
                                SDL_UpdateWindowSurface(fenetre);

                                SDL_Delay(1500);

                                boucle_infinie=0;
                            }
                            continue;


                        default:
                            if(pos_texte.x==150)
                                boucle_infinie=0;
                            else
                                continue;
                    }


                case SDL_KEYUP: //Si on relache une touche du clavier
                    switch(evenement.key.keysym.sym)
                    {
                        case SDLK_RIGHT:

                            if(pos_mario.x<400)
                            {
                                if(CurrentMario==mario[0])
                                {
                                    SDL_RenderClear(pers_mario);
                                    SDL_BlitSurface(Fond,NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                    SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                    SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                    SDL_UpdateWindowSurface(fenetre);
                                    CurrentMario=mario[1];
                                    pos_mario.x=pos_mario.x+3;
                                    SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                    SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                    SDL_RenderPresent(pers_mario);
                                }

                                if(CurrentMario==mario[1])
                                {
                                    SDL_RenderClear(pers_mario);
                                    SDL_BlitSurface(Fond,NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                    SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                    SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                    SDL_UpdateWindowSurface(fenetre);
                                    CurrentMario=mario[2];
                                    pos_mario.x=pos_mario.x+3;
                                    SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                    SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                    SDL_RenderPresent(pers_mario);
                                }

                                if(CurrentMario==mario[2])
                                {
                                    SDL_RenderClear(pers_mario);
                                    SDL_BlitSurface(Fond,NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                    SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                    SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                    SDL_UpdateWindowSurface(fenetre);
                                    CurrentMario=mario[3];
                                    pos_mario.x=pos_mario.x+3;
                                    SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                    SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                    SDL_RenderPresent(pers_mario);
                                }

                                if(CurrentMario==mario[3])
                                {
                                    SDL_RenderClear(pers_mario);
                                    SDL_BlitSurface(Fond,NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
                                    SDL_BlitSurface(support,NULL, SDL_GetWindowSurface(fenetre),&pos_support);
                                    SDL_BlitSurface(esi,NULL, SDL_GetWindowSurface(fenetre),&pos_esi);
                                    SDL_UpdateWindowSurface(fenetre);
                                    CurrentMario=mario[0];
                                    pos_mario.x=pos_mario.x+3;
                                    SDL_QueryTexture(CurrentMario,NULL,NULL,&pos_mario.w,&pos_mario.h);
                                    SDL_RenderCopy(pers_mario, CurrentMario,NULL,&pos_mario);
                                    SDL_RenderPresent(pers_mario);
                                }
                            }
                            else
                            {
                                    police = TTF_OpenFont("./SDL/mariofont.ttf",19);

                                    if(police==NULL)
                                    {
                                        SDL_Log("Impossible de charger la police > %s\n",SDL_GetError());
                                        exit(EXIT_FAILURE);
                                    }


                                    texte=TTF_RenderText_Blended(police, "Appuyez sur la touche Espace...", couleur_noire);

                                    SDL_BlitSurface(texte,NULL, SDL_GetWindowSurface(fenetre),&pos_texte);
                                    SDL_UpdateWindowSurface(fenetre);


                                    }
                            continue;

                        default:
                        if(pos_texte.x==150)
                                boucle_infinie=0;
                            else
                                continue;
                    }

                case SDL_QUIT:
                    SDL_FreeSurface(texte);
                    SDL_FreeSurface(boule_feu);
                    SDL_FreeSurface(flamme);
                    SDL_FreeSurface(support);
                    SDL_FreeSurface(esi);
                    SDL_DestroyTexture(CurrentMario);
                    SDL_DestroyTexture(mario[0]); SDL_DestroyTexture(mario[1]); SDL_DestroyTexture(mario[2]); SDL_DestroyTexture(mario[3]);
                    SDL_FreeSurface(Fond);
                    SDL_FreeSurface(icone);
                    TTF_Quit();
                    SDL_DestroyRenderer(pers_mario);
                    SDL_DestroyWindow(fenetre);
                    SDL_Quit();

                default:
                    if(pos_texte.x==150)
                                boucle_infinie=0;
                            else
                            continue;
            }
        }
    }


    Mix_HaltMusic();
    mario_song=Mix_LoadMUS("./SDL/Sons/olympic_hymn.mp3");
    Mix_PlayMusic(mario_song, 5);

    Fond=SDL_LoadBMP("./SDL/Images/JO.bmp");
    SDL_BlitSurface(Fond, NULL, SDL_GetWindowSurface(fenetre),&pos_fond);
    SDL_BlitSurface(welcome,NULL, SDL_GetWindowSurface(fenetre),&pos_welcome);
    SDL_UpdateWindowSurface(fenetre);

   police = TTF_OpenFont("./SDL/mariofont.ttf",17);

    if(police==NULL)
    {
        SDL_Log("Impossible de charger la police > %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }


    texte=TTF_RenderText_Blended(police, "Appuyez sur une touche", couleur_noire);

    pos_texte.x=285; pos_texte.y=550;

    SDL_BlitSurface(texte,NULL, SDL_GetWindowSurface(fenetre),&pos_texte);
    SDL_UpdateWindowSurface(fenetre);

    SDL_FreeSurface(texte);
    TTF_CloseFont(police);


    boucle_infinie=SDL_TRUE;
     while(boucle_infinie)
     {
        SDL_Event evenement;
        while(SDL_PollEvent(&evenement)) //Fonction qui capture tous les événements
        {
            switch(evenement.type)
            {
                case SDL_KEYDOWN:
                    boucle_infinie= 0;

                default:
                    break;

                case SDL_QUIT:
                    boucle_infinie=0;
            }
        }
     }





    Mix_HaltMusic();
    Mix_FreeMusic(mario_song);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(info);
    SDL_FreeSurface(boule_feu);
    SDL_FreeSurface(flamme);
    SDL_FreeSurface(support);
    SDL_FreeSurface(esi);
    SDL_DestroyTexture(CurrentMario);
    SDL_DestroyTexture(mario[0]); SDL_DestroyTexture(mario[1]); SDL_DestroyTexture(mario[2]); SDL_DestroyTexture(mario[3]);
    SDL_FreeSurface(Fond);
    SDL_FreeSurface(icone);
    TTF_Quit();
    SDL_DestroyRenderer(pers_mario);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}

