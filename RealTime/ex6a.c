/************************************************************************/
/*  EX6a.C : Communication par Boîtes à Lettres                         */
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
#define BL2     2
#define TBL2	1
#define TOBL2	0
#define BL3     3
#define TBL3	1
#define TOBL3	0

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
{
Word null;
while(1)
	{
	Receive(BL1,&null,TOBL1);
	EcrTexte(F1,"T11111\n");
	Tempo(10);
	EffaceFen(F1);
	Send(BL2,0);
	}
}
/*-------------------------------------------------------------------*/
Tache2(void)
{
Word null;
while(1)
	{
	Receive(BL2,&null,TOBL2);
	EcrTexte(F2,"T22222\n");
	Tempo(10);
	EffaceFen(F2);
	Send(BL3,0);
	}
}
/*-------------------------------------------------------------------*/
Tache3(void)
{
Word null;
while(1)
	{
	Receive(BL3,&null,TOBL3);
	EcrTexte(F3,"T33333\n");
	Tempo(10);
	EffaceFen(F3);
	Send(BL1,0);
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
InitMailBox(BL2,TBL2);
InitMailBox(BL3,TBL3);

CreateTask(TK,PTK,TKill);
CreateTask(T1,PT1,Tache1);
CreateTask(T2,PT2,Tache2);
CreateTask(T3,PT3,Tache3);

StartTask(TK);
StartTask(T1);
StartTask(T2);
StartTask(T3);

/* Pour une solution avec une seule BAL, cf ex6a-bis.c */


/* Amorcage */
Send(BL1,0);

while(1)
	{
	EcrCar(F4,'&');
	Tempo(2);
	}
}
