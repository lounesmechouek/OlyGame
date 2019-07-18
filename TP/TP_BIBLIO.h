#ifndef TP_BIBLIO_H_INCLUDED
#define TP_BIBLIO_H_INCLUDED
#define MaxPays 100
#define MaxEpreuves 77
#define MaxAthletes 10

///***************************************************  STRUCTURES DE DONNEES  ************************************************************
struct PAYS
{
    char Nom[40];
    int Present;
};
typedef struct PAYS PAYS;
//-----------------------------------------------------------------------------------------------------------------------------------------
struct EPREUVE
{
    char Nom[40];
    int Present;
};
typedef struct EPREUVE EPREUVE;
//------------------------------------------------------------------------------------------------------------------------------------------
struct ATHLETE
{
    char Nom[25];
    struct ATHLETE *suiv;
};
typedef struct ATHLETE ATHLETE;
//-------------------------------------------------------------------------------------------------------------------------------------------
struct NOMATHL
{
    char Nom[25];
    int Present;
};
typedef struct NOMATHL NOMATHL;

///*************************************************** PROTOTYPES DES PROCEDURES ***********************************************************
/*=========================================================================================================================================*/
/*  1) */void lecturealeatoire(char tabpays[][40], int nbpays, char tabepreuve[][40], int nbepreuves, ATHLETE *tabjo[MaxEpreuves][MaxPays]);
        //PROCEDURES ET FONCTIONS CREES POUR lecturealeatoire
int rand_a_b(int a,int b);
void remp_tabpays(char tabpays[][40], int nbpays);
void remp_tabepreuve(char tabepreuve[][40], int nbepreuves);
void remp_tabjo(char tabpays[][40], int nbpays, char tabepreuve[][40], int nbepreuves, ATHLETE *tabjo[MaxEpreuves][MaxPays]);
void tri_alpha(char T[][40],int taille);
int lire(char *chaine, int longueur,FILE*);
/*=========================================================================================================================================*/
/*  2) */void Insert_Ath(ATHLETE *TabJo[MaxEpreuves][MaxPays],char NomAth[],int NumPays,int NumEpreuve);
        //FONCTIONS CREES POUR Insert_Ath
int Nb_Joueurs (ATHLETE *Tete);
int Exist_Ath(ATHLETE *TabJo[MaxEpreuves][MaxPays], char NomAth[],int NumPays,int NumEpreuve);
/*=========================================================================================================================================*/
/*  3) */int Epreuve_Sans_Ath (ATHLETE *TabJo[MaxEpreuves][MaxPays],int NbPays,int NumEpreuve);
/*=========================================================================================================================================*/
/*  4) */void Supp_Athlete (ATHLETE *TabJo[MaxEpreuves][MaxPays],char NomAth [25],int NumPays,int NumEpreuve);
        //PROCEDURE CREE POUR Supp_Athlete
void Rech_Ath (ATHLETE *TabJo[MaxEpreuves][MaxPays],char NomAth[],int NumPays,int NumEpreuve,ATHLETE **Ath_Disqualifie,ATHLETE **Ath_Precedent);
/*=========================================================================================================================================*/
/*  5) */void suppays(ATHLETE *tabjo[MaxEpreuves][MaxPays], char tabpays[][40], int nbepreuves, int *nbpays, int NumPays);
/*=========================================================================================================================================*/
/*  6) */void supepreuve(ATHLETE *tabjo[MaxEpreuves][MaxPays], char tabepreuve[][40], int *nbepreuves, int nbpays, int ne);
/*=========================================================================================================================================*/
/*  7) */void suplignesvides (ATHLETE *tabjo[MaxEpreuves][MaxPays],int *nbepreuves,int nbpays,char tabepreuve[][40]);
/*=========================================================================================================================================*/
/*  8) */void listjo(char tabpays[][40], int nbpays, char tabepreuve[][40], int nbepreuves, ATHLETE *tabjo[MaxEpreuves][MaxPays]);
/*=========================================================================================================================================*/
/*  9) */void listathpays(char tabpays[][40], int nbpays, char tabepreuve[][40], int nbepreuves, ATHLETE *tabjo[MaxEpreuves][MaxPays]);
/*=========================================================================================================================================*/

///*******************************************************************************************************************************************

///************************************
/*      MACHINE ABSTRAITE   */
/*===================================*/
char *NOM (ATHLETE *p);
/*===================================*/
ATHLETE *SUIVANT ( ATHLETE *P);
/*===================================*/
void AFF_ADR ( ATHLETE *p, ATHLETE *Q);
/*===================================*/
void AFF_NOM( ATHLETE *p, char name[]);
/*===================================*/
void DISQUALIFIER( ATHLETE *p);
/*===================================*/
void CONVOQUER (ATHLETE **p);
///************************************

///****************************************************GRAPHISME *************************************************************///
 /*===================================*/
 int menuprincipal(void);
 /*===================================*/
 int Menu2(void);
 /*===================================*/
 void Documentation ();
 /*===================================*/
 void ChoixMenu ();
 /*===================================*/
 void clear_screen(void);
 /*===================================*/
 void contacter();
 /*===================================*/
 void fin ();
 /*===================================*/
 void affich_tabepreuve_droite(char tabepreuves[][40], int nbepreuve);
 /*===================================*/
 void affich_tab(char tab[][40], int nb,int posx);
 /*===================================*/
 void list_pays_epreuve( int nump, int ne, ATHLETE *tabjo[MaxEpreuves][MaxPays]);


#endif // TP_BIBLIO_H_INCLUDED
