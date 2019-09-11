/************************************************************************/
/*  EX6b.C : Communication par Boîtes à Lettres                         */
/************************************************************************/
/* Fonction :                                                           */
/*  Cet exercice est la prolongation de l'exercice 6a.                  */
/*  Trois tâches T1,T2 et T3 tournent "circulairement" dans l'ordre     */
/*  T1,T2,T3.                                                           */
/*  Chaque tâche Ti possède sa propre fenêtre et écrit "Tiiiii". Le     */
/*  message reste affiché pendant environ une seconde, puis la fenêtre  */
/*  est effacée. La tâche suivante prend alors la main.                 */
/*  Comme dans la plupart des exercices, une tâche TKill, permet        */
/*  par la frappe de Escape de revenir au DOS.                          */
/*  Ce qui est nouveau, c'est qu'un cycle T1,T2,T3 est déclenché        */
/*  par la frappe d'une touche autre que Escape.                        */
/*      UNE TOUCHE <=> UN CYCLE T1,T2,T3.                               */
/*  La frappe d'une touche est sans effet tant que le cycle T1,T2,T3    */
/*  n'est pas terminé.                                                  */
/* Principe :                                                           */
/*  La synchronisation est assurée par boîtes à lettres.                */
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

/* On peut acceder a cette variable globale sans section critique car l'environnememt n'est pas preemptif */
Char cycle = 1; /*Est-on dans un cycle ?*/

#include "tempo.c"
/*-------------------------------------------------------------------*/
TKill(void)
{
Char car;
while(1)
	{
	LireCar(F4,OFF,&car);
	if(cycle == 0)
		{
		if(car == ESC) RetDos();
		cycle = 1;
		Send(BL1,0);
		}
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
	/*On n'envoie pas de message a T1*/
	cycle = 0;
	}
}
/*-------------------------------------------------------------------*/
void main(void)
{
InitVideo();
F0 = OuvreFen( 0, 0,78,24, noir, blanc, "EXERCICE 6b : COMMUNICATION PAR BOITES A LETTRES");
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

Send(BL1,0);

while(1)
	{
	EcrCar(F4,'&');
	Tempo(2);
	}
}

