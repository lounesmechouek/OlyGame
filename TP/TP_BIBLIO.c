#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP_BIBLIO.h"

/*CETTE BIBLIOTHEQUE CONTIENT TOUTES LES PROCEDURES (NON GRAPHIQUES) QUI ONT SERVI A LA REALISATION DU TP.*/


            ///******************************************************************************************************///
            ///                                        MACHINE ABSTRAITE                                             ///
            ///******************************************************************************************************///

///--------------------Rend la chaine contenue dans le champ Nom du maillon pointé par P ------------------------------------///
    char *NOM (ATHLETE *p)
    {
        return p->Nom;
    }

///--------------------Rend l'adresse du maillon qui suit P ----------------------------------------------------------------///
    ATHLETE *SUIVANT ( ATHLETE *P)
    {
        return (P->suiv);
    }
///--------------------Affecte l'adresse Q dans le champ suiv de P ---------------------------------------------------------///
    void AFF_ADR ( ATHLETE *p, ATHLETE *Q)
    {
        p->suiv=Q;
    }
///--------------------Affecte name dans le champ Nom de p -----------------------------------------------------------------///
    void AFF_NOM( ATHLETE *p, char name[])
    {
        strcpy(p->Nom,name);
    }
///--------------------libère l'espace mémoire occupé par p-----------------------------------------------------------------///
    void DISQUALIFIER( ATHLETE *p)
    {
        free (p);
    }
///--------------------Alloue un espace mémoire au maillon pointé par P-----------------------------------------------------///
    void CONVOQUER (ATHLETE **p)
    {
        (*p)=malloc(sizeof(ATHLETE));
    }
///**********************************************FIN DE LA MACHINE ABSTRAITE *********************************************////




   /*=================================================================================================================*/
  /* -------------------------------------FONCTIONS ET PROCEDURES DU TP---------------------------------------------- */
 /*===================================================================================================================*/



///******************************************************************************************************///
/// lecturealeatoire: GENERE tabpays,tabepreuve et tabjo                                                 ///
///******************************************************************************************************///

void lecturealeatoire(char tabpays[][40], int nbpays, char tabepreuve[][40], int nbepreuves, ATHLETE *tabjo[MaxEpreuves][MaxPays])
{
    remp_tabpays(tabpays,nbpays);
    tri_alpha(tabpays,nbpays);
    remp_tabepreuve(tabepreuve,nbepreuves);
    tri_alpha(tabepreuve,nbepreuves);
    remp_tabjo(tabpays, nbpays, tabepreuve, nbepreuves, tabjo);
}


    /*==============PROCEDURES ET FONCTIONS UTILISEES PAR "lecturealeatoire"=====================:*/

///======================================================================================================///
/// rand_a_b :GENERE UN NOMBRE ENTIER APPARTENANT A [a,b[                                                ///
///======================================================================================================///

int rand_a_b(int a,int b)
{
    return rand()%(b-a) +a;
}

///======================================================================================================///
/// remp_tabpays:REMPLIT LE TABLEAU "tabpays" A  "nbpays" ELEMENTS                                       ///
///======================================================================================================///

void remp_tabpays(char tabpays[][40], int nbpays)
{
/// DECLARATIONS DE VARIABLES.
int i=0,j=1,num_alea=0;
char country[36];
PAYS TOUS_PAYS[MaxPays];


/// IMPORTATION DES PAYS STOCKES DANS LE FICHIER VERS LE TABLEAU TOUS_PAYS.
    for (i=0;i<MaxPays;i++)
            TOUS_PAYS[i].Present=0;                 /*ON INITIALISE TOUS LES CHAMPS DE PRESENCE A 0.*/


    FILE *PAYS=fopen("PAYS.txt","r");

    if(PAYS==NULL)
        exit(1);                                    /*ON VERIFIE QUE LE FICHIER S'EST BIEN OUVERT*/
    else

    {

        for (i=0;i<MaxPays;i++)
        {
            fgets(country,35,PAYS);
            for(j=0;j<strlen(country);j++)
                TOUS_PAYS[i].Nom[j]=country[j];        /*ON REMPLIT LE TABLEAU CONTENANT TOUS LES PAYS*/
            TOUS_PAYS[i].Nom[j]='\0';
            TOUS_PAYS[i].Present=1;

        }

    }

    fclose(PAYS);

/// REMPLISSAGE ALEATOIRE DE TABPAYS

    if(nbpays>MaxPays)
        printf("VOUS AVEZ ENTRE UN NOMBRE DE PAYS TROP GRAND!");

    else
    {
        i=0; j=0;
        while(i<nbpays)
        {
            num_alea=rand_a_b(0,MaxPays);
            if(TOUS_PAYS[num_alea].Present)
            {
                for(j=0;j<strlen(TOUS_PAYS[num_alea].Nom);j++)          /*ON REMPLIT LE TABLEAU tabpays.*/
                    tabpays[i][j]=TOUS_PAYS[num_alea].Nom[j];

                tabpays[i][j]='\0';
                TOUS_PAYS[num_alea].Present=0;
                i++;
            }
        }

     }
}

///======================================================================================================///
/// remp_tabepreuve:REMPLIT LE TABLEAU "tabepreuves" A  "nbepreuves" ELEMENTS                            ///
///======================================================================================================///

void remp_tabepreuve(char tabepreuve[][40], int nbepreuves)
  {
    /// DECLARATIONS VARIABLES
    char epreuve[36];
    int i=0,j=0, num_alea=0;
    EPREUVE TOUTES_EPREUVES[MaxEpreuves];


    ///EXPORTATION DES NOMS D'EPREUVES DANS "TOUTES_EPREUVES" A PARTIR DU FICHIER
    for (i=0;i<MaxEpreuves;i++)
            TOUTES_EPREUVES[i].Present=0;                 //ON INITIALISE TOUS LES CHAMPS DE PRESENCE A 0.


    FILE *EPREUVES=fopen("EPREUVES.txt","r");

    if(EPREUVES==NULL)
        exit(1);                                        //ON VERIFIE QUE LE FICHIER S'EST BIEN OUVERT
    else

    {

        for (i=0;i<MaxEpreuves;i++)
        {
            fgets(epreuve,35,EPREUVES);
            for(j=0;j<strlen(epreuve);j++)
                TOUTES_EPREUVES[i].Nom[j]=epreuve[j];        //ON REMPLIT LE TABLEAU CONTENANT TOUTES LES EPREUVES.
            TOUTES_EPREUVES[i].Nom[j]='\0';
            TOUTES_EPREUVES[i].Present=1;

        }
    }

    fclose(EPREUVES);

    ///REMPLISSAGE ALEATOIRE DE TABEPREUVES

    if(nbepreuves>MaxEpreuves)
        printf("VOUS AVEZ ENTRE UN NOMBRE D'EPREUVES TROP GRAND");

    else
    {
        i=0; j=0;
        while(i<nbepreuves)
        {

            num_alea=rand_a_b(0,MaxEpreuves);
            if(TOUTES_EPREUVES[num_alea].Present)
            {
                for(j=0;j<strlen(TOUTES_EPREUVES[num_alea].Nom);j++)          //ON REMPLIT LE TABLEAU FINAL D'EPREUVES SELECTIONNEES.
                    tabepreuve[i][j]=TOUTES_EPREUVES[num_alea].Nom[j];

                tabepreuve[i][j]='\0';
                TOUTES_EPREUVES[num_alea].Present=0;
                i++;
            }
        }

    }
}


///======================================================================================================///
/// lire : PERMET D'EXTRAINE chaine de LONGUEUR longueur A PARTIR DE file DE MANIERE SECURISEE           ///
///======================================================================================================///

int lire(char *chaine, int longueur,FILE* file)
{
    char *positionEntree = NULL;

    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, file) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

///======================================================================================================///
/// remp_tabjo: REMPLIT LE TABLEAU "tabjo" A "nbpays" COLONNES ET "nbepreuves" LIGNES                    ///
///======================================================================================================///

void remp_tabjo(char tabpays[][40], int nbpays, char tabepreuve[][40], int nbepreuves, ATHLETE *tabjo[MaxEpreuves][MaxPays])
{
    ///DECLARATION DE VARIABLES
    char region[10], reg[10], Name[25], pays[25], tabregion[MaxPays][9];

    NOMATHL tabathl[MaxEpreuves*10];

    PAYS TOUS_PAYS[MaxPays];

    int colonne,ligne,na,cpt,NomCorrect,num_alea,i,j;

    ATHLETE *athl1=NULL,*athl2=NULL;

    FILE *REGION=NULL;


    /// REMPLISSAGE TABLEAUX
    /* ------------------------------------------------------------------------------------------------------------------------ */
    /*ON IMPORTE LE FICHIER DES PAYS AINSI QUE LA REGION DE CHAQUE PAYS*/
    FILE *GLOBAL=fopen("REGION.txt","r");
    FILE *PAYS=fopen("PAYS.txt","r");

    for(i=0;i<MaxPays;i++)
    {
        fgets(region,9,GLOBAL);
        fgets(pays,25,PAYS);

        for(j=0;j<strlen(region);j++)
            tabregion[i][j]=region[j];

        tabregion[i][j]='\0';

        for(j=0;j<strlen(pays);j++)
            TOUS_PAYS[i].Nom[j]=pays[j];

        TOUS_PAYS[i].Nom[j]='\0';
        TOUS_PAYS[i].Present=0;
    }
    fclose(GLOBAL);
    fclose(PAYS);

    /* ------------------------------------------------------------------------------------------------------------------------ */

    ///REMPLISSAGE TABJO

    for(colonne=0;colonne<nbpays;colonne++)
    {
        for(j=0;j<MaxPays;j++)
         {
            if(!(strcmp((TOUS_PAYS[j].Nom),tabpays[colonne])))
            {
                for(i=0;i<7;i++)
                    reg[i]=tabregion[j][i];         /*ON SELECTIONNE LA REGION CORRESPONDANT AU PAYS TIRE.*/
                reg[6]='\0';
            }

         }

        REGION=fopen(reg,"r");

        if(REGION==NULL)
            exit(1);

        else
        {
                for(i=0;i<(MaxEpreuves*10);i++)
                {
                    lire(Name,25,REGION);           /*REMPLISSAGE D'UN TABLEAU INTERMEDIAIRE QUI NOUS PERMETTRA */
                    strcpy(tabathl[i].Nom,Name);     /*DE SAVOIR SI UN ATHLETE A DEJA ETE SELECTIONNE.           */
                    tabathl[i].Present=0;
                }

            for(ligne=0;ligne<nbepreuves;ligne++)
            {
                na=rand_a_b(0,11);
                if(na==0)
                    tabjo[ligne][colonne]=NULL;

                else
                {
                    for(cpt=1;cpt<=na;cpt++)
                    {
                        NomCorrect=0;
                        CONVOQUER(&athl1);
                        while(!(NomCorrect))
                        {
                            num_alea=rand_a_b(0,(MaxEpreuves*10));
                            if(tabathl[num_alea].Present==0)
                            {
                                NomCorrect=1;
                                tabathl[num_alea].Present=1;
                                AFF_NOM(athl1,tabathl[num_alea].Nom);


                            }
                        }

                        AFF_ADR(athl1,NULL);
                        if(cpt==1)
                            tabjo[ligne][colonne]=athl1;   /* SI C'EST LE PREMIER ATHLETE PIOCHE ALORS ON LE MET DANS */
                        else                               /* LA CASE DE tabjo. SINON ON LE CHAINE JUSTE AU PRECEDENT. */
                            AFF_ADR(athl2,athl1);
                        athl2=athl1;
                    }
            }

        }
        fclose(REGION);
        }
    }


}

///======================================================================================================///
/// tri_alpha: TRIE ALPHABETIQUEMENT LE TABLEAU "T"                                                      ///
///======================================================================================================///

void tri_alpha(char T[][40],int taille)
{
    ///DECLARATIONS
    int i,j;        /*VARIABLES DE PARCOURS*/
    char temp[40]; /*CHAINE TEMPORAIRE POUR LA PERMUTATION*/

    ///TRAITEMENT
    for (i=0;i<taille-1;i++)
    {
        for (j=i+1;j<taille;j++)
        {
            if (strcmp(T[i],T[j])>0)
            {
            strcpy(temp,T[i]);
            strcpy(T[i],T[j]);
            strcpy(T[j],temp);
            }
        }
    }
}


///******************************************************************************************************///
/// Insert_Ath: INSERTION D'UN NOUVEL ATHLETE "NomAth" DANS TabJo[NumEpreuve][NumPays]                   ///
///******************************************************************************************************///

void Insert_Ath(ATHLETE *TabJo[MaxEpreuves][MaxPays],char NomAth[],int NumPays,int NumEpreuve)
{

    if ((!Exist_Ath(TabJo,NomAth,NumPays,NumEpreuve)) && (Nb_Joueurs(TabJo[NumEpreuve-1][NumPays-1])<MaxAthletes))
    // VERIFICATION : il y a moins de maxathlètes athlètes déjà inscrits, et NomAth ne figure pas dans la liste.
    {
        //ALLOCATION D'UN NOUVEL ESPACE MEMOIRE
        ATHLETE *Nouveau_Joueur;
        CONVOQUER(&Nouveau_Joueur);

        //CONSTRUCTION DU MAILLON ET CHAINAGE (du nouvel athlete)
        AFF_NOM(Nouveau_Joueur,NomAth);
        AFF_ADR(Nouveau_Joueur,TabJo[NumEpreuve-1][NumPays-1]);
        TabJo[NumEpreuve-1][NumPays-1]=Nouveau_Joueur;


    }
    else
    {
       if (Exist_Ath(TabJo,NomAth,NumPays,NumEpreuve))
            printf("L'ATHLETE %s EXISTE DEJA.\n",NomAth);
       if (Nb_Joueurs(TabJo[NumEpreuve-1][NumPays-1])>=MaxAthletes)
            printf("LA LISTE EST SATUREE!\n");

    }
}

        /*==============FONCTIONS UTILISEES PAR "Insert_Ath" =====================:*/


///======================================================================================================///
/// Nb_Joueurs: Rend le nombre de joueurs dans une liste pointée par "tete                               ///
///======================================================================================================///
int Nb_Joueurs (ATHLETE *Tete)
{
    ATHLETE *p;
    int cpt=0;
    p=Tete;

    while (p!=NULL)
    {
        cpt++;
        p=SUIVANT(p);
    }
    return (cpt);
}

///======================================================================================================///
/// Exist_Ath: REND 1 SI "NomAth" EXISTE DANS LA LISTE TabJo[NumEpreuve][NumPays], 0 SINON               ///
///======================================================================================================///

int Exist_Ath(ATHLETE *TabJo[MaxEpreuves][MaxPays], char NomAth[],int NumPays,int NumEpreuve)
{
    ATHLETE *p; //pointeur de parcours de la liste
    p=TabJo[NumEpreuve-1][NumPays-1];

    while ((p!=NULL) && (strcmp(NOM(p),NomAth)!=0))
            p=SUIVANT(p);

    if (p==NULL)return 0;
    else return 1;
}

///******************************************************************************************************///
/// Epreuve_Sans_Ath: REND 1 SI L'EPREUVE NumEpreuve EST SANS ATHLETES, 0 SINON                          ///
///******************************************************************************************************///
int Epreuve_Sans_Ath (ATHLETE *TabJo[MaxEpreuves][MaxPays],int NbPays,int NumEpreuve)
{
    int pays;
    /*PARCOURS DE TOUS LES PAYS DISPONIBLES */
    for (pays=0;pays<NbPays;pays++)
        if (TabJo[NumEpreuve-1][pays]!=NULL) return 0;

    return 1;
}

///******************************************************************************************************///
/// Supp_Athlete: SUPPRESION D'UN ATHLETE "NomAth" DANS TabJo[NumEpreuve][NumPays]                      ///
///******************************************************************************************************///

void Supp_Athlete (ATHLETE *TabJo[MaxEpreuves][MaxPays],char NomAth [25],int NumPays,int NumEpreuve)
{
    /*VERIFICATION DE L'EXISTANCE */
    if (!Exist_Ath(TabJo,NomAth,NumPays,NumEpreuve))
            printf("\n\t *L'athlete %s ne fait pas partie de la selection. \n",NomAth);

    else
    {
        ATHLETE *Ath_Disq=NULL;
        ATHLETE *Ath_Prec=NULL;

        /*RECHERCHE DE LA POSITION DE L'ATHLETE DISQUALIFIE (POUR LE CHAINAGE)*/
        Rech_Ath(TabJo,NomAth,NumPays,NumEpreuve,&Ath_Disq,&Ath_Prec);

        /*CAS OU L'ATHLETE DISQUALIFIE REPRESENTE LA TETE */
        if (Ath_Disq==TabJo[NumEpreuve-1][NumPays-1])
        {
            TabJo[NumEpreuve-1][NumPays-1]=SUIVANT(TabJo[NumEpreuve-1][NumPays-1]);
            DISQUALIFIER(Ath_Disq);
        }
        /*L'ATHELETE DISQUALIFIE EST DIFFERENT DE LA TETE */
        else
        {
            AFF_ADR(Ath_Prec,SUIVANT(Ath_Disq));
            DISQUALIFIER(Ath_Disq);
        }
    }

}

        /*==============PROCEDURE CREE POUR : Supp_Athlete=====================:*/

///======================================================================================================///
/// Rech_Ath: RECHERCHE L'ATHLETE "NomAth" DANS TabJo[NumEpreuve][NumPays] ET LE RANGE DANS              ///
///                "Ath_Disqualifie" ET SON PRECEDENT  DANS Ath_Precedent                                ///
///======================================================================================================///

void Rech_Ath (ATHLETE *TabJo[MaxEpreuves][MaxPays],char NomAth[],int NumPays,int NumEpreuve,ATHLETE **Ath_Disqualifie,ATHLETE **Ath_Precedent)
{
    /*DECLARATIONS */
    ATHLETE *p;
    p=TabJo[NumEpreuve-1][NumPays-1];//tete

    *Ath_Disqualifie=NULL;
    *Ath_Precedent=NULL;

    /*RECHERCHE SEQUENTIELLE */
    while((p!=NULL) && (strcmp(NOM(p),NomAth)!=0))
    {
        *Ath_Precedent=p;
        p=SUIVANT(p);
    }
    if(strcmp(NOM(p),NomAth)==0) *Ath_Disqualifie =p; //SI L'ATHLETE N'EST PAS PRESENT


}
///******************************************************************************************************///
/// supepreuve: SUPPRIME L'EPREUVE ne DE tabjo ET DE tabepreuve                                          ///
///******************************************************************************************************///
void supepreuve(ATHLETE *tabjo[MaxEpreuves][MaxPays], char tabepreuve[][40], int *nbepreuves, int nbpays, int ne)
{

    if(*nbepreuves > 0)
   {

    int i=0,j=0;
    ATHLETE *p, *q;
    ///EFFACEMMENT DANS tabepreuve
    for(i=ne-1;i<*nbepreuves-1;i++)
        strcpy(tabepreuve[i],tabepreuve[i+1]);

    ///EFFACEMMENT DANS tabjo
    //ON LIBERE L'ESPACE MEMOIRE
    for(j=0;j<nbpays;j++)
        {
            p=tabjo[ne-1][j];
            while (p!=NULL)
            {
                q=SUIVANT(p);
                DISQUALIFIER(p);
                p=q;
            }
        }

    if(*nbepreuves > 1)
    {
    //ON EFFECTUE UN DECALAGE VERS LE HAUT
    for(i=ne-1;i<*nbepreuves-1;i++)
    {
        for(j=0;j<nbpays;j++)
            tabjo[i][j]=tabjo[i+1][j];
    }

    //ON LIBERE L'ESPACE MEMOIRE OCCUPE PAR LA DERNIERE LIGNE
    for(j=0;j<nbpays;j++)
        {
            p=tabjo[*nbepreuves-1][j];
            while (p!=NULL)
            {
                q=SUIVANT(p);
                DISQUALIFIER(p);
                p=q;
            }
        }
    }

    *nbepreuves=*nbepreuves-1;
   }

   else
    printf("Il n'y a pas d'epreuves a supprimer");
}


///******************************************************************************************************///
/// suppays: SUPPRIME LE PAYS NumPays DE tabjo ET DE tabpays                                            ///
///*****************************************************************************************************///
void suppays(ATHLETE *tabjo[MaxEpreuves][MaxPays], char tabpays[][40], int nbepreuves, int *nbpays, int NumPays)
{
    int i=0,j=0;
    ATHLETE *p, *q;
    ///EFFACEMMENT DANS tabpays
    for(i=NumPays-1;i<*nbpays-1;i++)
        strcpy(tabpays[i],tabpays[i+1]);


    if(*nbpays > 0)
    {

    ///EFFACEMMENT DANS tabjo
    //ON LIBERE L'ESPACE MEMOIRE
    for(i=0;i<nbepreuves;i++)
        {
            p=tabjo[i][NumPays-1];
            while (p!=NULL)
            {
                q=SUIVANT(p);
                DISQUALIFIER(p);
                p=q;
            }
        }

    if(*nbpays > 1)
    {

    //ON EFFECTUE UN DECALAGE VERS LA GAUCHE
    for(i=0;i<nbepreuves;i++)
    {
        for(j=NumPays-1;j<*nbpays-1;j++)
            tabjo[i][j]=tabjo[i][j+1];


    }

    //ON LIBERE L'ESPACE MEMOIRE OCCUPE PAR LA DERNIERE COLONNE
    for(i=0;i<nbepreuves;i++)
        {
            p=tabjo[i][*nbpays-1];
            while (p!=NULL)
            {
                q=SUIVANT(p);
                DISQUALIFIER(p);
                p=q;
            }
        }
    }


    *nbpays=*nbpays-1;
    }

    else
        printf("Il n'ya pas de pays a supprimer");
}


///******************************************************************************************************///
/// suplignesvides: SUPPRIME TOUTES LES EPREUVES SANS ATHLETES                                          ///
///*****************************************************************************************************///

void suplignesvides (ATHLETE *tabjo[MaxEpreuves][MaxPays],int *nbepreuves,int nbpays,char tabepreuve[][40])
{
    int i;

    for (i=0;i<*nbepreuves;i++)
    {
        //VERIFICATION SI L'EPREUVE EST SANS ATHLETE POUR SUPPRIMER LA LIGNE CORRESPONDANTE
        if (Epreuve_Sans_Ath(tabjo,nbpays,i+1))
            supepreuve(tabjo,tabepreuve,nbepreuves,nbpays,i+1);
    }

}

///******************************************************************************************************///
/// listathpays: AFFICHE LES ATHLETES INSCRITS AU PAYS nump                                             ///
///*****************************************************************************************************///

void listathpays(char tabpays[][40], int nump, char tabepreuve[][40], int nbepreuves, ATHLETE *tabjo[MaxEpreuves][MaxPays])
{
    /*PREPARATION DU BACKGROUND */
    clear_screen();
    /*DECLARATIONS */
    ATHLETE *p;
    int  j=0 ,cpt=0,x=2,y=17,k=17,t=0;
    int cond=0;//condition pour afficher (cond=1 si un athlete ,au moins, est present )

    /*POSITIONNEMENT DU CURSEUR ET TRAITEMENT DE L'AFFICHAGE*/
    gotoxy(x,y);
    //AFFICHAGE DU NOM DU PAYS
    textbackground(68);for (t;t!=149;t++)printf(" ");t=0;printf("\n");textbackground(15);
    printf("%60c  PAYS : %3s   \n",' ', tabpays[nump-1]);
    textbackground(68);for (t;t!=149;t++)printf(" ");t=0;textbackground(15);
     //CAS OU AUCUN ATHLETE EST PRESENT POUR LE PAYS

    for(j=0;j<nbepreuves;j++)
    {
        if(tabjo[j][nump-1]!=NULL)
        {
            cond =1;
            break;
        }
    }
    /*TRAITEMENT PAR EPREUVE */
    if (cond==1) //AU MOINS UN ATHELET EST PRESENT
    {
    //AFFICHAGE DES NOMS D'ATHLETES PAR EPREUVE
    k=k+5;
        for(j=0;j<nbepreuves;j++)
        {
            if(tabjo[j][nump-1]!=NULL)
            {
            y=k;
            cpt++;
            gotoxy(x,y);
            printf("=============================");
            gotoxy(x,y+1);
            printf("%5s",tabepreuve[j]);
            gotoxy(x,y+2);
            printf("=============================");
            y=y+3;

                p=tabjo[j][nump-1];
                //AFFICHAGE DE LA LISTE D'ATHLETES POUR L'EPREUVE j
                while(p!=NULL)
                {
                    gotoxy(x,y);
                    printf("%5s",NOM(p));
                    p=SUIVANT(p);
                    y++;
                }
        /*AFFICHAGE: TRAITEMENT DU POSITIONNEMENT DES LISTES */
        if (cpt!=3)
        {
            x=x+50;
        }
        else
        {
            y=y+8;
            k=y;
            x=2;
            cpt=0;
        }
        }
        }

    }
    else //LA LISTE D'ATHLETE POUR LE PAYS EST VIDE

    {
        textcolor(5);printf("%50c AUCUN ATHLETE DISPONIBLE!\n",' ');textcolor(0);
    }
}
///******************************************************************************************************///
/// listjo: AFFICHE LES ATHLETES INSCRITS AUX JO PAR PAYS ET PAR EPREUVE                                ///
///*****************************************************************************************************///

void listjo(char tabpays[][40], int nbpays, char tabepreuve[][40], int nbepreuves, ATHLETE *tabjo[MaxEpreuves][MaxPays])
{
    /*DECLARATIONS */
    int i=0, j=0 ,cpt=0,x=2,y=17,k=17,t=0;
    int cond=0;//condition pour afficher (cond=1 si un athlete ,au moins, est present )

    ATHLETE *p;

    /*TRAITEMENT PAR PAYS*/
    for(i=0;i<nbpays;i++)
    {
        cond=0;
        for(j=0;j<nbepreuves;j++)
        {
            if(tabjo[j][i]!=NULL)
            {
                cond=1;
                break;//SORTIE DE BOUCLE DES QU'ON TROUVE UNE LISTE D'EPREUVES NON VIDE POUR LE PAYS
            }
        }

        if (cond==1)/*ON N'AFFICHE QUE LES PAYS QUI PRESENTENT DES ATHLETES*/
        {

        //AFFICHAGE DU NOM DU PAYS
        gotoxy(x,y);
        textbackground(68); for (t;t!=149;t++)printf(" ");t=0;printf("\n");textbackground(15);
        printf("%60c  PAYS : %3s   \n",' ', tabpays[i]);
        textbackground(68);for (t;t!=149;t++)printf(" ");t=0;textbackground(15);
        k=k+5;

        /*TRAITEMENT PAR EPREUVE */

        for(j=0;j<nbepreuves;j++)
        {
            if(tabjo[j][i]!=NULL) //AFFICHAGE FAIT DANS LE CAS OU UN ATHLETE AU MOINS SE PRESENTE A L'EPREUVE
            {
            y=k;
            cpt++;
            gotoxy(x,y);
            printf("=============================");
            gotoxy(x,y+1);
            printf("%5s",tabepreuve[j]);
            gotoxy(x,y+2);
            printf("=============================");
            y=y+3;

                p=tabjo[j][i];
                //AFFICHAGE DES NOMS D'ATHLETES INSCRITS A L'EPREUVE j
                while(p!=NULL)
                {
                    gotoxy(x,y);
                    printf("%5s",NOM(p));
                    p=SUIVANT(p);
                    y++;
                }

        if (cpt!=3)
        {
            x=x+50;
        }
        else
        {
            y=y+8;
            k=y;
            x=2;
            cpt=0;
        }
        }
        }
     x=2;
     y=k+12;k=y;
     cpt=0;

    }
}

}

