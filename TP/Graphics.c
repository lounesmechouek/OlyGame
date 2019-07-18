#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "TP_BIBLIO.h"
#include "conio2.h"
#include "conio.h"
#define Tmp 10
#define CR 0x0D
 int menuprincipal(void)
{

    gotoxy(28, 15);
    textcolor(RED);printf("\t\t\t\t---- MENU PRINCIPAL ----\n\n\n\n");textcolor(BLACK);

     char menu[4][100]={"\t01) A propos du logo des jeux olympiques"
         ,"\t02) Chargement des noms d'athletes dans la base de donnees "
         ,"\t03) Nous contacter"
         ,"\t03) Quitter le programme"};


   int choix = 1, i;
   int key ;

   do
   {
      for (i = 1; i <= 4; i++)
      {
         if (choix == i) //teste si le compteur est = au menu selection
            {
                textbackground(68); //TEXTE SELECTIONNE
                textcolor(WHITE);
            }
         else
         {
             textcolor(BLACK);
             textbackground(WHITE); //TEXTE NORMAL
         }

         gotoxy(45, i + 17);
         cprintf("%s", menu[i - 1]);
      }
        //TRAITEMENT DES TOUCHES DE DEPLACEMENT
   TOUCHE:if (kbhit()) //VERIFIE SI UNE TOUCHE A ETE ENCLANCHEE
         {
            key = getch();

            switch (key)
            {
            case 80: //BAS
               choix++;
               if (choix > 4)
               {
                  choix = 1; //RETOUR AU DEBUT APRES LE DEPLACEMENT VERS LE BAS EN ETANT AU DERNIER CHOIX
               }
               break;
            case 72://HAUT
               choix--;
               if (choix < 1)
               {
                  choix= 4;//RETOUR A LA FIN APRES LE DEPLACEMENT VERS LE HAUT EN ETANT AU PREMIER CHOIX
               }
               break;
            }
         }
         else goto TOUCHE;//POUR EVITER DES BOUCLES FOR EN PLUS

   }
   while (key != CR ); //FIN DE "tant que" lorsqu'on appuie sur ENTRER
   return choix;
}


 int Menu2(void)
{
gotoxy(28, 15);
textcolor(RED);printf("\t\t---- CHOISISSEZ UNE OPTION ----\n\n");textcolor(BLACK);
char menu [12][100]={
         "\t01) Affichage de tous les pays participants\n"
         ,"\t02) Affichage de toutes les épreuves disponibles\n"
         ,"\t03) Affichage d'une liste de joueurs pour un pays de votre choix\n"
         ,"\t04) Affichage des listes des joueurs pour tous les pays et toutes les epreuves\n"
         ,"\t05) Vérifier si une épreuve est sans athlètes\n"
         ,"\t06) Ajouter un nouvel athlete\n"
         ,"\t07) Supprimer un athlete disqualfie\n"
         ,"\t08) Supprimer une épreuve donnée\n"
         ,"\t09) Supprimer un pays disqualfie\n"
         ,"\t10) Supprimer toutes les épreuves vides\n"
         ,"\t11) Retour au menu principal"
         ,"\t12) Quitter le programme"};
   int choix = 1, i;
   int key ;

   do
   {
      for (i = 1; i <= 12; i++)
      {
         if (choix == i)
            {
                textbackground(68); //TEXTE SELECTIONNE
                textcolor(WHITE);
            }
         else
         {
             textcolor(BLACK);
             textbackground(WHITE); //TEXTE NORMAL
         }

         gotoxy(30, i + 17);
         cprintf("%s", menu[i - 1]);
      }
         //TRAITEMENT DES TOUCHES DE DEPLACEMENT
     OPTION:if (kbhit()) //VERIFIE SI UNE TOUCHE EST ENCLANCHEE
         {
            key = getch();

            switch (key)
            {
            case 80://BAS
               choix++;
               if (choix > 12)
               {
                  choix = 1; //RETOUR AU DEBUT APRES LE DEPLACEMENT VERS LE BAS EN ETANT AU PREMIER CHOIX
               }
               break;
            case 72://HAUT
               choix--;
               if (choix < 1)
               {
                  choix= 12;//RETOUR A LA FIN APRES LE DEPLACEMENT VERS LE HAUT EN ETANT AU PREMIER CHOIX
               }
               break;
            }
         }
         else goto OPTION;//POUR EVITER DES BOUCLES FOR EN PLUS

   }
   while (key != CR ); //SORTIE DE BOUCLE EN CLIQUANT SUR ENTRER
   return choix;
}
/********/
void Documentation ()
{

    gotoxy(5,15);
    textcolor(RED);printf("\t\t\t*-*-*-*-*-*-*- A PROPOS DU LOGO DES JEUX OLYMPIQUES *-*-*-*-*-*-*\n\n\n");
    textcolor(BLACK);

    printf("\tLes cinq anneaux entrelaces representent les cinq continents unis par l'olympisme,\n");
    printf("\tet les six couleurs (en comptant le blanc en arriere-plan) representent toutes les\n");
    printf("\tnations, car au moins l'une de ces couleurs etait presente dans le drapeau de chaque\n");
    printf("\tpays, a l'epoque de sa creation en 1913. Ainsi ce drapeau est le symbole de l'universalite\n");
    printf("\tde l'esprit olympique.\n\n");
    printf("\tL'interpretation courante associe un continent a chaque couleur des anneaux :\n");
    printf("\t ");textbackground(GREEN);printf(" ");textbackground(15);printf(" Le vert: "); printf("l'Oceanie \n");
    printf("\t ");textbackground(0);printf(" ");textbackground(15);printf(" Le noir: ");printf("l'Afrique \n");
    printf("\t ");textbackground(YELLOW);printf(" ");textbackground(15);printf(" Le jaune: ");printf("l'Asie \n");
    printf("\t ");textbackground(BLUE);printf(" ");textbackground(15);printf(" Le bleu: ");printf("l'Europe \n");
    printf("\t ");textbackground(12);printf(" ");textbackground(15);printf(" Le rouge: ");printf("l'Amerique \n\n");
    printf("\tElle est refutee par le Comite international olympique qui associe les couleurs des anneaux\n");
    printf("\taux couleurs des drapeaux trouves sur les cinq continents. \n");

}
/*******/
void ChoixMenu ()
{
/*DECLARATIONS */
ATHLETE *tabjo[MaxEpreuves][MaxPays];
char tabepreuve[MaxEpreuves][40],tabpays[MaxPays][40];
int nbepreuves,nbpays,i,nump,ne,key,Choice,choice2;
char Name[40];

do
{
MENUPRINC:
clear_screen();
Choice=menuprincipal();
switch (Choice)
 {
     case 1: /*-----------------DOCUMENTATION *-------------------------*/
     {
      clear_screen();
      Documentation();
      system("pause");
      goto MENUPRINC;
     }
     break;

    case 2: /*-----------------CHARGEMENT DE LA BASE DE DONNEES *-------------------------*/
    {
        clear_screen();

        printf("\t*-*-*-*-*-* BIENVENUE SUR LE PROGRAMME DE CREATION DES LISTES DES PARICIPANTS AUX JO ! *-*-*-*-*-*-* \n\n");
        printf("COMBIEN DE PAYS VONT PRENDRE PART A CET EVENEMENT ? ");
        textcolor(RED);scanf("%d", &nbpays);textcolor(BLACK);

        while ((nbpays<1)||(nbpays>MaxPays))
                    {
                       textcolor(RED);printf("\n NUMERO ERRONE ! VEUILLEZ REESSAYER (max.%d):",MaxPays);
                       scanf("%d",&nbpays);textcolor(BLACK);
                    }

        printf("MERVEILLEUX ! ET COMBIEN D'EPREUVES VONT ETRE DISPUTEES ? ");
        textcolor(RED);scanf("%d", &nbepreuves);textcolor(BLACK);

        while ((nbepreuves<1)||(nbepreuves>MaxEpreuves))
                    {
                       textcolor(RED);printf("\n NUMERO ERRONE ! VEUILLEZ REESSAYER (max.%d):",MaxEpreuves);
                       scanf("%d",&nbepreuves);textcolor(BLACK);
                    }

        textcolor(RED);printf("\n\t\t\t\tBIEN NOTE ! LE TIRAGE AU SORT POUR DESIGNER LES PAYS ET LES EPREUVES EST EN COURS ! \n\n");
        textcolor(BLACK);
        lecturealeatoire(tabpays,nbpays,tabepreuve,nbepreuves,tabjo);
        gotoxy(50,27);

        //ANIMATION DE CHARGEMENT
        int cp=0;
        for (cp; cp!=21; cp++)
        {
            textbackground(12);
            textcolor(WHITE);
            gotoxy(58,27);
            printf("            CHARGEMENT %d %%            ", cp*5);
            delay(100);
        }
        textbackground(15);
        textcolor(BLACK);
        printf("\n\n");

        system("pause");
        do
        {
MENUSEC:    clear_screen(); /*-----------------ACCES AU MENU SECONDAIRE *-------------------------*/
            choice2=Menu2();
            switch (choice2)
            {
             case 1: /*-----------------LISTE DES PAYS *-------------------------*/
                {
                   clear_screen();
                   textcolor(RED);printf("\t\t----------------*-*-*-* LES PAYS PARTICIPANTS *-*-*-*---------------- \n");textcolor(BLACK);
                   if (nbpays!=0)affich_tab(tabpays,nbpays,18);
                   else printf("\n\n\t\tAUCUN PAYS DISPONIBLE!");

                system("pause");
                goto MENUSEC;
                }
                break;

            case 2: /*-----------------LISTE DES EPREUVES *-------------------------*/
                {
                clear_screen();
                  textcolor(RED);printf("\t\t----------------*-*-*-* LES EPREUVES DISPONIBLES *-*-*-*----------------\n");textcolor(BLACK);
                 if (nbepreuves!=0)affich_tab(tabepreuve,nbepreuves,18);
                 else printf("\n\n\t\tAUCUNE EPREUVE DISPONIBLE!");
                 system("pause");
                goto MENUSEC;
                }
                break;
            case 3: /*-----------------LISTE DES JOUEURS POUR UN PAYS *-------------------------*/
                {
                    clear_screen();
                    textcolor(RED);printf("----------------*-*-*-* LISTE DES JOUEURS POUR UN PAYS DONNE *-*-*-*----------------\n");textcolor(BLACK);
                    if (nbpays!=0)
                    {
                    affich_tab(tabpays,nbpays,18);
                    printf("\n ENTREZ LE NUMERO DU PAYS :");
                    scanf("%d",&nump);

                    while ((nump<1)||(nump>nbpays))
                    {
                       printf("\n NUMERO ERRONE ! VEUILLEZ REESSAYER.");
                       scanf("%d",&nump);
                    }

                    textcolor(RED);printf("\t * LE PAYS CHOISI EST: %s \n\n\n",tabpays[nump-1]);
                    textcolor(BLACK);
                    system("pause");


                    listathpays(tabpays,nump,tabepreuve,nbepreuves,tabjo);
                    }
                    else printf("\n\n\t\tAUCUN PAYS DISPONIBLE!");
                system("pause");
                goto MENUSEC;
                }
                break;
             case 4 : /*-----------------LISTE DE TOUS LES JOUEURS *-------------------------*/
                {
                    clear_screen();
                    textcolor(RED);printf("------------*-*-* AFFICHAGE DES PARTICIPANTS PAR PAYS ET PAR EPREUVE*-*-*---------------\n");textcolor(BLACK);
                    if (nbpays !=0)
                    {
                        if (nbepreuves!=0)listjo(tabpays,nbpays,tabepreuve,nbepreuves,tabjo);
                        else printf("\n\n\t\tAUCUNE EPREUVE DISPONIBLE!");
                    }
                    else printf("\n\n\t\tAUCUN PAYS DISPONIBLE!");


                system("pause");
                goto MENUSEC;
                }
                break;
            case 5 : /*----------------- EPREUVE SANS ATHLETES*-------------------------*/
                {
                    clear_screen();
                    textcolor(RED);printf("------------*-*-* VERIFICATION D'EPREUVES SANS ATHLETES *-*-*---------------\n");textcolor(BLACK);
                    if (nbepreuves!=0)
                    {
                    affich_tab(tabepreuve,nbepreuves,18);

                    printf("QUEL EST LE NUMERO DE L'EPREUVE SUR LAQUELLE VOUS VOULEZ FAIRE UNE VERIFICATION?");
                    scanf("%d",&ne);
                    while ((ne<1)||ne>nbepreuves)
                    {
                        printf("NUMERO ERRONE! VEUILLEZ REESAYER: ");
                        scanf("%d",&ne);
                    }
                     textcolor(RED);
                    if (Epreuve_Sans_Ath(tabjo,nbpays,ne))
                       printf("L'EPREUVE NE PRESENTE AUCUN ATHLETE! \n\n");

                    else

                        printf("L'EPREUVE N'EST PAS SANS ATHLETES.\n");
                textcolor(BLACK);
                    }
                    else printf("\n\n\t\tAUCUNE EPREUVE DISPONIBLE!");
                system("pause");
                goto MENUSEC;
                }
                break;
            case 6 : /*----------------- AJOUT D'UN ATHLETE *-------------------------*/
                {
                    int m;
                    clear_screen();
                    textcolor(RED);printf("------------*-*-* AJOUT D'UN NOUVEL ATHLETE *-*-*---------------\n");textcolor(BLACK);

                    printf("ENTREZ LE NOM DU NOUVEL ATHLETE:");
                    textcolor(RED);scanf("%s",&Name);textcolor(BLACK);

                    if (nbpays!=0)
                    {
                    affich_tab(tabpays,nbpays,18);
                    gotoxy(1,wherey()+2);
                    m=wherey()+3;
                    printf("QUEL EST LE NUMERO DE SON PAYS ?");
                    textcolor(RED);scanf("%d",&nump);textcolor(BLACK);

                    while ((nump<1)||(nump>nbpays))
                    {
                        printf("NUMERO ERRONE! VEUILLEZ REESSAYER:");
                        textcolor(RED);scanf("%d",&nump);textcolor(BLACK);
                    }

                    if (nbepreuves!=0)
                    {
                    affich_tab_droite(tabepreuve,nbepreuves);
                    gotoxy(1,m);

                    printf("QUELLE EST L'EPREUVE A LAQUELLE IL PARTICIPE?");
                    textcolor(RED);scanf("%d",&ne);textcolor(BLACK);

                    while ((ne<1)||(ne>nbepreuves))
                    {
                        printf("NUMERO ERRONE! VEUILLEZ REESSAYER:");
                        textcolor(RED);scanf("%d",&ne);textcolor(BLACK);
                    }
                    int nbjr=Nb_Joueurs(tabjo[ne-1][nump-1]);
                    textcolor(RED);Insert_Ath(tabjo,Name,nump,ne);textcolor(BLACK);

                    //SI L'AJOUT A ETE FAIT
                    if (nbjr!=Nb_Joueurs(tabjo[ne-1][nump-1]))
                    {
                    textcolor(RED);printf("AJOUT EN COURS..."); textcolor(BLACK); system("pause");
                    textcolor(RED);printf("\n\n\n LA NOUVELLE LISTE DES JOUEURS EST :\n");textcolor(BLACK);
                    list_pays_epreuve(nump,ne,tabjo);
                    }
                    }
                    else printf("\n\n\t\tAJOUT IMPOSSIBLE! AUCUNE EPREUVE DISPONIBLE!");
                    }
                    else printf("\n\n\t\tAJOUT IMPOSSIBLE! AUCUN PAYS DISPONIBLE!");
                system("pause");
                goto MENUSEC;
                }
                break;
            case 7: /*----------------- SUPPRESSION D'UN ATHLETE -------------------------*/
                {
                    clear_screen();
                    int max;
                    textcolor(RED);printf("------------*-*-* SUPPRESSION D'UN ATHLETE DIQUALIFIE *-*-*---------------\n");textcolor(BLACK);
                    printf("ENTREZ LE NOM DE L'ATHLETE DISQUALIFE:");
                    textcolor(RED);scanf("%s",&Name);textcolor(BLACK);

                    if (nbpays!=0)
                    {

                    gotoxy(50,17);printf("PAYS:");
                    affich_tab(tabpays,nbpays,18);
                    gotoxy(1,wherey()+2);
                    max=wherey()+3;

                    printf("QUEL EST LE NUMERO DE SON PAYS ?");
                    textcolor(RED);scanf("%d",&nump);textcolor(BLACK);

                    while ((nump<1)||(nump>nbpays))
                    {
                        printf("NUMERO ERRONE! VEUILLEZ REESSAYER:");
                        textcolor(RED);scanf("%d",&nump);textcolor(BLACK);
                    }
                    textcolor(BLACK);

                    if (nbepreuves!=0)
                    {

                    affich_tab_droite(tabepreuve,nbepreuves);


                    gotoxy(1,max);
                    printf("QUELLE EST L'EPREUVE A LAQUELLE IL PARTICIPE?");
                    textcolor(RED);scanf("%d",&ne);textcolor(BLACK);

                    while ((ne<1)||(ne>nbepreuves))
                    {
                        printf("NUMERO ERRONE! VEUILLEZ REESSAYER:");
                        textcolor(RED);scanf("%d",&ne);textcolor(BLACK);
                    }
                    int nbj=Nb_Joueurs(tabjo [ne-1][nump-1]);
                    textcolor(RED);
                    Supp_Athlete(tabjo,Name,nump,ne);
                    textcolor(BLACK);

                    //SI LA SUPPRESSION A ETE EFFECTUEE
                    if (nbj!=Nb_Joueurs(tabjo [ne-1][nump-1]))
                    {
                        if (Nb_Joueurs(tabjo [ne-1][nump-1])!=0)
                        {
                            textcolor(RED);printf("SUPPRESION EN COURS..."); textcolor(BLACK);system("pause");
                            textcolor(RED);printf("\n\n\n LA NOUVELLE LISTE DES JOUEURS EST :\n");textcolor(BLACK);
                            list_pays_epreuve(nump,ne,tabjo);
                        }
                        else textcolor(RED);printf("\n\n\n LA LISTE DES JOUEURS EST VIDE.\n");textcolor(BLACK);

                    }
                    }
                    else printf("\n\n\t\tSUPPRESSION IMPOSSIBLE! AUCUNE EPREUVE DISPONIBLE!");
                    }
                    else printf("\n\n\t\tSUPPRESSION IMPOSSIBLE! AUCUN PAYS DISPONIBLE!");

                system("pause");
                goto MENUSEC;
                }
                break;
            case 8: /*-----------------SUPPRESSION D'UNE EPREUVE *-------------------------*/
                {
                    clear_screen();
                    textcolor(RED);printf("------------*-*-* SUPPRESSION D'UNE EPREUVE DONNEE *-*-*---------------\n");textcolor(BLACK);

                    if (nbepreuves!=0)
                    {

                    affich_tab(tabepreuve,nbepreuves,18);
                    printf("QUELLE EST LE NUMERO DE L'EPREUVE QUE VOUS VOULEZ SUPPRIMER?  ");
                    textcolor(RED);scanf("%d",&ne);textcolor(BLACK);

                    while((ne<1)||(ne>nbepreuves))
                    {
                        printf("NUMERO ERRONE! VEUILLEZ REESSAYER: ");
                        scanf("%s",&ne);
                    }

                    supepreuve(tabjo,tabepreuve,&nbepreuves,nbpays,ne);
                    textcolor(RED);printf("SUPPRESION EN COURS..."); textcolor(BLACK);
                    system("pause");

                    if (nbepreuves!=0)
                    {
                        printf("\nLA NOUVELLE LISTE D'EPREUVES EST: \n");
                        affich_tab(tabepreuve,nbepreuves,wherey()+2);
                    }
                    else printf("AUCUNE EPREUVE DISPONIBLE AUX JEUX OLYMPIQUES!");
                    }
                    else printf("\n\n\t\tSUPPRESSION IMPOSSIBLE! AUCUNE EPREUVE DISPONIBLE!");
                system("pause");
                goto MENUSEC;
                }
                break;
            case 9: /*-----------------SUPPRESSION D'UN PAYS *-------------------------*/
                {
                    clear_screen();
                    textcolor(RED);printf("------------*-*-* SUPPRESSION D'UN PAYS DIQUALIFIE *-*-*---------------\n");textcolor(BLACK);

                    if (nbpays!=0)
                    {

                    affich_tab(tabpays,nbpays,18);
                    printf("ENTREZ LE NUMERO DU PAYS DISQUALIFE:");
                    textcolor(RED);scanf("%d",&nump);textcolor(BLACK);

                    while ((nump<1)||(nump>nbpays))
                    {
                        printf("NUMERO ERRONE! VEUILLEZ REESSAYER:");
                        textcolor(RED);scanf("%d",&nump);textcolor(BLACK);
                    }
                    suppays(tabjo,tabpays,nbepreuves,&nbpays,nump);
                    textcolor(RED);printf("SUPPRESSION EN COURS..."); textcolor(BLACK);system("pause");
                    if (nbpays!=0)affich_tab(tabpays,nbpays,wherey()+2);
                    else printf("AUCUN PAYS DISPONIBLE AUX JEUX OLYMPIQUES!");
                    }
                    else printf("\n\n\t\t SUPPRESSION IMPOSSIBLE! AUCUN PAYS DISPONIBLE!");
                system("pause");
                goto MENUSEC;
                }
                break;
                case 10: /*----------------- SUPPRESSION DE TOUTES LES EPREUVES SANS ATHLETES-------------------------*/
                {
                    clear_screen();
                    textcolor(RED);printf("------------*-*-* SUPPRESSION DE TOUTES LES EPREUVES SANS ATHLETES *-*-*---------------\n");textcolor(BLACK);

                    textcolor(RED);printf("SUPPRESSION EN COURS..."); textcolor(BLACK);system("pause");
                    suplignesvides(tabjo,&nbepreuves,nbpays,tabepreuve);
                    if (nbepreuves!=0)
                    {
                        printf("DESORMAIS, LES EPREUVES SUIVANTES PRESENTENT TOUTES DES ATHLETES : \n\n");
                        affich_tab(tabepreuve,nbepreuves,20);
                    }
                    else printf("\n\n\t\tAUCUNE EPREUVE DISPONIBLE!");
                system("pause");
                goto MENUSEC;
                }
                break;
            case 11: /*-----------------RETOUR AU MENU PRINCIPAL *-------------------------*/
                goto MENUPRINC;
            break;

            case 12: /*----------------- SORTIE DU PROGRAMME -------------------------*/
                {
                system("color F0");
                clear_screen();
                fin();
                exit(0);
                }
            break;

            }
            break;
        getch();
        key=getch();
        }while (key!=27);
    }
    break;

case 3: /*----------------- CONTACT -------------------------*/
    {
        clear_screen();
        contacter();
        printf("\n");
    system("pause");
    goto MENUPRINC;
    }
    break;

case 4: /*-----------------SORTIE DU PROGRAMME -------------------------*/
    {
        system("color F0");
        clear_screen();
        fin();
    exit(0);
    }
    break;
 }
 break;

getch();
key=getch();
}while (key!=27);
}

/****/
void clear_screen(void)
{
    system("cls");
    int i=0;
    system("mode con LINES=30000 COLS=150");
    textbackground(68);
    textcolor(15);
    for (i;i!=150;i++) printf(" ");
    i=32;
    printf("  REALISE PAR: AOUAOUCHE Louiza & MECHOUEK Lounes");
    for (i;i!=100; i++) printf(" "); printf("2017/2018 - 1CPI2  ");
    i=0;
    for (i;i!=150;i++) printf(" ");i=0;
    for (i;i!=150;i++) printf(" ");i=0;
    for (i;i!=35;i++) printf(" ");for (i;i!=110;i++) printf("%c", 220); for (i=110;i!=150;i++) printf(" "); i=0;
    for (i;i!=35;i++) printf(" ");printf("%c", 219); for (i=35;i!=108;i++) printf(" "); printf("%c", 219); for (i=108;i!=150;i++) printf(" "); i=0;
    for (i;i!=33;i++) printf(" ");printf("%c                 ECOLE NATIONALE SUPERIEURE D'INFORMATIQUE               %c", 219, 219); for (i=108;i!=150;i++) printf(" "); i=0;
    for (i;i!=33;i++) printf(" ");printf("%c", 219); for (i=33;i!=106;i++) printf(" "); printf("%c", 219); for (i=106;i!=150;i++) printf(" "); i=0;
    for (i;i!=31;i++) printf(" ");printf("%c   TP1:-- GESTION DES LISTES D'ATHLETES INSCRITS AUX JEUX OLYMPIQUES --  %c", 219, 219); for (i=108;i!=150;i++) printf(" "); i=0;
    for (i;i!=33;i++) printf(" ");printf("%c", 219); for (i=33;i!=106;i++) printf(" "); printf("%c", 219); for (i=106;i!=150;i++) printf(" "); i=0;
    for (i;i!=31;i++) printf(" ");for (i;i!=106;i++) printf("%c", 223); for (i=106;i!=160;i++) printf(" ");i=0;
    for (i;i!=150;i++) printf(" ");
    gotoxy(15,15);

    textbackground(WHITE);
    textcolor(BLACK);
}
void contacter()
{
    int i=0;
    gotoxy(15,15);for(i;i!=105;i++)printf("%c",219);i=0;
    gotoxy(15,16);printf("%c",219);gotoxy(119,16); ;printf("%c",219);
    gotoxy(15,17);printf("%c ADRESSES E-MAIL:",219);gotoxy(119,17); ;printf("%c",219);
    gotoxy(15,18);printf("%c",219);gotoxy(119,18); ;printf("%c",219);
    gotoxy(15,19);printf("%c       * MECHOUEK Lounes :   hl_mechouek@esi.dz",219);gotoxy(119,19); ;printf("%c",219);
    gotoxy(15,20);printf("%c",219);gotoxy(119,20); ;printf("%c",219);
    gotoxy(15,21);printf("%c       * AOUAOUCHE Louiza:   hl_aouaouche@esi.dz",219);gotoxy(119,21); ;printf("%c",219);
    gotoxy(15,22);printf("%c",219);gotoxy(119,22); ;printf("%c",219);
    gotoxy(15,23);for(i;i!=105;i++)printf("%c",219);i=0;

}

void fin ()
{
    int i=0;


    gotoxy(15,19);printf("                 ~              A          B   I   E   N   T   O   T   !               ~");
    gotoxy(15,21);printf("                                        \n\n\n\n\n");
}
void affich_tab_droite(char tabepreuves[][40], int nbepreuve)
///AFFICHAGE VERTICAL DES EPREUVES
{

    int i,k;
    int ind=18;
    int p=18;
    gotoxy(100,17);printf("EPREUVES:");
    for (i=0;i<nbepreuve;i++)
    {
        gotoxy(100,ind);ind+=2;
        if (i==0)printf("%c",218);
        else printf("%c",195);

        for(k=0;k<40;k++)printf("%c",196);

        if (i==0)printf("%c",191);
        else printf("%c",180);

        gotoxy(100,p+1);p++;printf("%c",179);
        gotoxy(101,p);printf("%d |%s",i+1,tabepreuves[i]);
        gotoxy(141,p);printf("%c",179);

        gotoxy(100,p+1);p++;
        if (i==nbepreuve-1)
        {
            printf("%c",192);
            for(k=0;k<40;k++)printf("%c",196);
            printf("%c",217);
        }
    }

    printf("\n");
}
void affich_tab(char tab[][40], int nb,int posx)
///AFFICHAGE VERTICAL DES ELEMENTS DE tab
{

    int i,k;
    int ind=posx;
    int p=posx;
    for (i=0;i<nb;i++)
    {
        gotoxy(50,ind);ind+=2;
        if (i==0)printf("%c",218);
        else printf("%c",195);

        for(k=0;k<40;k++)printf("%c",196);

        if (i==0)printf("%c",191);
        else printf("%c",180);

        gotoxy(50,p+1);p++;printf("%c",179);
        gotoxy(51,p);printf("%d |%s",i+1,tab[i]);
        gotoxy(91,p);printf("%c",179);

        gotoxy(50,p+1);p++;
        if (i==nb-1)
        {
            printf("%c",192);
            for(k=0;k<40;k++)printf("%c",196);
            printf("%c",217);
        }
    }

    printf("\n");
}
void list_pays_epreuve( int nump, int ne, ATHLETE *tabjo[MaxEpreuves][MaxPays])
///AFFICHE LA LISTE DES JOUEURS DU PAYS nump et L'EPREUVE ne
{
    ATHLETE *p;
    int k,x;
        printf("\n\t\t\t\t\t\t\t");
        p=tabjo[ne-1][nump-1];
        if (p!=NULL)
        {

        for (x=0;x<25;x++)
        {
            textbackground(RED);printf(" ");
        }
        textbackground(WHITE);printf("\n");
        k=1;
        printf("\n");
        while(p!=NULL)
            {
               printf("\t\t\t\t\t\t\t%d:%15s\n",k,NOM(p));
               k++;
               p=SUIVANT(p);
            }
        }
}
