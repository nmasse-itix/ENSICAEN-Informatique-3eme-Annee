/************************************************************************/
/* EX1.C : Multi-Fenêtrage avec seulement UNE tâche                     */
/************************************************************************/
/* Fonction :                                                           */
/*  Création de fenêtres avec le système de Multi-Fenêtrage VIDEO       */
/*  et opérations d'affichage dans les fenêtres.                        */
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define T1      1       /*Outre la tâche main, il n'y a dans cette exercice que la tâche T1 qui a le numéro 1*/
			/*Rappel : le numéro peut varier de 1 à 10. La valeur 0 est reservée à la tâche main*/

#define PT1     3       /*La priorité de la tâche T1 est PT1=3 (pourquoi pas?). La priorité peut varier de 1 à 10*/
			/*La priorité la plus forte correspond à la valeur 10. La tâche main a la priorité 0*/

#define ESC     0x1b    /*On revient au DOS en frappant sur la touche Escape*/

Word    F0,F1,F2,F3,F4,F5,F6;/*On utilise 6 fenêtres dans cet exercice*/

#include "tempo.c"      /*Le fichier tempo.c est dans le répertoire courant et correspond à une boucle d'attente logicielle*/
			/*La syntaxe d'appel est Tempo(Word Duree). La valeur de Duree correspond approximativement*/
			/*à la durée de la boucle (en millisecondes) pour les PC utilisés en TP*/

/*--------------------------------------------------------------------------------------------------*/
Tache_Controleur(void)
{
/*Deux tâches dans cet exercice :
- la tâche main (incontournable)
- la tâche Tache_Controleur*/

Char Car;
EcrTexte(F5,"Tapez des chiffres entre 1 et 4 ; ESC pour sortir\r");

while (TRUE)
	{
	LireCar(F5, ON, &Car);  /*Rappel : la fonction LireCar est suspensive*/
	switch (Car)
		{
		case ESC : RetDos(); break;     /*RetDos est une fonction du noyau*/
		case '1' : Proc_1(); break;     /*Les fonctions Proc_i sont extrémement simples (cf. ci-dessous)*/
		case '2' : Proc_2(); break;
		case '3' : Proc_3(); break;
		case '4' : Proc_4(); break;
    }
  }
}
/*--------------------------------------------------------------------------------------------------*/
Proc_1(void)
{
EcrTexte(F1,"Proc_1 En Cours\n");
Tempo(2);      /*Boucle d'attente logicielle*/
EffaceFen(F1);
}

Proc_2(void)
{
EcrTexte(F2,"Proc_2 En Cours\n");
Tempo(5);
EffaceFen(F2);
}

Proc_3(void)
{
EcrTexte(F3,"Proc_3 En Cours\n");
Tempo(10);
EffaceFen(F3);
}

Proc_4(void)
{
static Int Cpt=0;
EcrTexte(F4,"Proc_4 En Cours\r");
SelectFen(F4);
EcrVar("Cpt = %d\r", Cpt);
Cpt ++;
if(Cpt == 3)
	{
	Cpt = 0;
	Tempo(10);
	EffaceFen(F4);
	}
}
/*--------------------------------------------------------------------------------------------------*/
void main(void)
{
InitVideo();            /*Appel obligatoire avant toute utilisation du module video*/

F0=OuvreFen( 0, 0,79,24, noir,   blanc, "EXERCICE1");
F1=OuvreFen( 1, 6,39, 9, cyan,   blanc, "Proc_1");
F2=OuvreFen(41, 6,78, 9, vert,   blanc, "Proc_2");
F3=OuvreFen( 1,11,39,14, bleu,   blanc, "Proc_3");
F4=OuvreFen(41,11,78,19, marron, blanc, "Proc_4");
F5=OuvreFen( 1, 1,78, 5, rouge,  blanc, "Tâche_Contrôleur");
F6=OuvreFen( 1, 20,78, 23, rouge,  blanc, "Tâche_Main");

InitNoyau();            /*Obligatoire pour utiliser le module video*/

CreateTask(T1,PT1,Tache_Controleur);    /*Créer la tâche numéro T1, avec la priorité T1, correspondant la fonction Tâche_controleur*/
										/*La TCB (partiellement initialisée est créée)*/

StartTask(T1);  /*La TCB est totalement initialisée : La tâche est prête*/
										/*Le tableau TabPrio est mis à jour*/

while (TRUE)
{
EcrTexte(F6,"&"); /*Affiche un "&"*/
Tempo(2);	  /*Simulation d'une charge CPU durant 2 dixieme de secondes*/
}
}