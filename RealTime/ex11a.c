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

#define	T1	1
#define	T2	2
#define	TK	3

#define	PT1	1
#define	PT2	1
#define	PTK	3

#define	Ress1	1
#define	Ress2	2

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
Tache1(void)
{
while(1)
	{
	P(Ress1,0);
	EcrTexte(F1,"Ress1\r");
	Tempo(5);
	P(Ress2,0);
	EcrTexte(F1,"Ress2");
	Tempo(5);
	EffaceFen(F1);
	V(Ress2);
	V(Ress1);
	}
}
/*-------------------------------------------------------------------*/
Tache2(void)
{
while(1)
	{

	/* Prise des ressources dans le meme ordre que T1
	pour eviter le phenomene d'interblocage */

	P(Ress1,0);
	EcrTexte(F2,"Ress1\r");
	Tempo(5);
	P(Ress2,0);
	EcrTexte(F2,"Ress2");
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
