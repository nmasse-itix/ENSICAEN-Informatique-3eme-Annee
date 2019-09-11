/************************************************************************/
/*  EX6a-bis.C : Communication par une seule Boîtes à Lettres           */
/************************************************************************/
/* Fonction :                                                           */
/*  Trois tâches T1,T2 et T3 tournent "circulairement" dans l'ordre     */
/*  T1,T2,T3.                                                           */
/*  Chaque tâche Ti possède sa propre fenêtre et écrit "Tiiiiii".       */
/*  Le message reste affiché pendant environ une demie seconde, puis    */
/*  la fenêtre est éffacée. La tâche suivante prend alors la main.      */
/*  Comme dans la plupart des exercices, une tâche TKill, de            */
/*  priorité supérieure, écrit les caractères frappés au clavier        */
/*  dans la fenêtre de la tâche T1. Escape permet de revenir au DOS.    */
/* Principe :                                                           */
/*  Les tâches se synchronisent mutuellement par boîtes à lettres.      */
/* 									*/
/* 									*/
/* Ajout:								*/
/*   - Une seule boite aux lettres utilisees                            */
/* 									*/
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define T1      1
#define T2      2
#define T3      3
#define TK      4

#define PT1     3
#define PT2     3
#define PT3     3
#define PTK     4

#define BL1     1
#define TBL1	1
#define TOBL1	0

#define ESC     0x1b

Word    F0,F1,F2,F3,F4;

#include "tempo.c"
/*-------------------------------------------------------------------*/
TKill(void)
{
Char car;
while(1)
	{
	LireCar(F4,ON,&car);
	if(car == ESC) RetDos();
	}
}
/*-------------------------------------------------------------------*/
Tache1(void)
{         			/*Les taches 1, 2 et 3 ne font que consommer */
Word null;
Receive(BL1,&null,TOBL1);       /*Met la tache dans la file d'attente de la boite aux lettres*/
while(1)
	{
	EcrTexte(F1,"T11111\n");
	Tempo(10);
	EffaceFen(F1);
	Receive(BL1,&null,TOBL1);	/*Remise de la tache dans la file d'attente de la boite aux lettres*/
	}
}
/*-------------------------------------------------------------------*/
Tache2(void)
{
Word null;
Receive(BL1,&null,TOBL1);
while(1)
	{
	EcrTexte(F2,"T22222\n");
	Tempo(10);
	EffaceFen(F2);
	Receive(BL1,&null,TOBL1);
	}
}
/*-------------------------------------------------------------------*/
Tache3(void)
{
Word null;
Receive(BL1,&null,TOBL1);
while(1)
	{
	EcrTexte(F3,"T33333\n");
	Tempo(10);
	EffaceFen(F3);
	Receive(BL1,&null,TOBL1);
	}
}
/*-------------------------------------------------------------------*/
void main(void)
{
InitVideo();
F0 = OuvreFen( 0, 0,78,24, noir, blanc, "EXERCICE 6a : COMMUNICATION PAR BOITES A LETTRES");
F1 = OuvreFen(10,10,21,13, vert, blanc, "TACHE 1");
F2 = OuvreFen(30, 3,41, 6, bleu, blanc, "TACHE 2");
F3 = OuvreFen(50,10,61,13, rouge,blanc, "TACHE 3");
F4 = OuvreFen( 2,20,77,23, cyan ,blanc, "TACHE MAIN");

InitNoyau();

InitMailBox(BL1,TBL1);

CreateTask(TK,PTK,TKill);
CreateTask(T1,PT1,Tache1);
CreateTask(T2,PT2,Tache2);
CreateTask(T3,PT3,Tache3);

/*On n'a pas besoin de section critique, car toutes les tache seront bloquees des leur debut */

StartTask(TK);
StartTask(T1); /*Inscription de T1 dans la file d'attente de la BAL*/
StartTask(T2); /*Inscription de T2 dans la file d'attente de la BAL*/
StartTask(T3); /*Inscription de T3 dans la file d'attente de la BAL*/

while(1)
	{
	Send(BL1,0);	/*La tache main ne fait que produire*/
	EcrCar(F4,'E');
	}
}
