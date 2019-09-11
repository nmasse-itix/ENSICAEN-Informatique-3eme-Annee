/************************************************************************/
/* EX11.C	INTERBLOCAGE alias ETREINTE FATALE alias DEAD LOCK	*/
/************************************************************************/
/* Fonction :								*/
/*  Deux tâches de même priorité travaillent en partage du temps.	*/
/*  Ces deux tâches utilisent DEUX ressources communes.			*/
/*  Si l'on ne prend pas de précaution, ce qui est le cas dans cet	*/
/*  exercice : CA BLOQUE !!!						*/
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

/* #include <stdlib.h> */

#define	T1	1
#define	T2	2
#define	TK	3

#define	PT1	1
#define	PT2	1
#define	PTK	3

#define	Ress1	1
#define	Ress2	2

#define DELAY   5

#define	ESC	0x1b

Word	F0,F1,F2,F3;

#include "tempo.c"
/*-------------------------------------------------------------------*/
TKill(void)
{
Char Msg1;
while(1)
	{
	LireCar(F1,ON,&Msg1);
	if( Msg1 == ESC ) RetDos();
	}
}
/*-------------------------------------------------------------------*/


/* La fonction random n'existe pas, nous l'avons recodee */
int random(int max) {
	return rand() % max;
}


Tache1(void)
{
Int cmpt = 0;
while(1)
	{
	while (1)
		{
		P(Ress1,0);
		EcrTexte(F1,"Ress1\r");
		Tempo(1);

		/* Si la ressource est disponible on la prend et on sort de la boucle */
		if (!TestP(Ress2)) break;

		/* Sinon, on relache la ressource et on attend un delai aleatoire */
		V(Ress1);
		EffaceFen(F1);
		DelayTask(random(DELAY) + 1);
		}

	++cmpt;

	EcrTexte(F1,"Ress2\r\n");
	SelectFen(F1);
	EcrVar("%d execution(s)\r\n",cmpt);
	Tempo(5);
	EffaceFen(F1);

	/* Liberation des ressources */
	V(Ress2);
	V(Ress1);
	}
}
/*-------------------------------------------------------------------*/
Tache2(void)
{
Int cmpt = 0;
while(1)
	{
	while (1)
		{
		P(Ress2,0);
		EcrTexte(F2,"Ress2\r");
		Tempo(1);

		if (!TestP(Ress1)) break;

		V(Ress2);
		EffaceFen(F2);
		DelayTask(random(DELAY) + 1);
		}

	++cmpt;
	EcrTexte(F2,"Ress1\r\n");
	SelectFen(F2);
	EcrVar("%d execution(s)\r\n",cmpt);
	Tempo(5);
	EffaceFen(F2);
	V(Ress1);
	V(Ress2);
	}
}
/*-------------------------------------------------------------------*/
void main(void)
{
InitVideo();
F0 = OuvreFen( 0, 0,79,24, noir, blanc, "EX 11 : INTERBLOCAGE alias ETREINTE FATALE alias DEAD LOCK");
F1 = OuvreFen( 5, 5,30,15, bleu, blanc, "T1 En Cours");
F2 = OuvreFen(40, 5,65,15, vert, blanc, "T2 En Cours");
F3 = OuvreFen( 2,20,77,23, cyan, blanc, "TACHE MAIN");

InitNoyau();

CreateTask(T1, PT1, Tache1);
CreateTask(T2, PT2, Tache2);
CreateTask(TK, PTK, TKill);

InitSemaphore(Ress1, 1); V(Ress1);
InitSemaphore(Ress2, 1); V(Ress2);

EnterRegion();
StartTask(T2);
StartTask(T1);
StartTask(TK);
RTClockInit(1);
LeaveRegion();

while(1)
	{
	EnterRegion();
	EcrCar(F3,'&');
	LeaveRegion();
	Tempo(2);
	}
}
