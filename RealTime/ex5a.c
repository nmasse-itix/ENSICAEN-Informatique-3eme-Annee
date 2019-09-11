/************************************************************************/
/* EX5A.C : Synchronisation par Sémaphore Binaire			*/
/************************************************************************/
/* Fonction :								*/
/*  Deux tâches de même priorité affichent chacune un message dans	*/
/*  leur fenêtre respective.						*/
/*  Ces deux tâches se synchronisent mutuellement.			*/
/* Principe : 								*/
/*  La synchronisation est realisée par un sémaphore binaire : ce	*/
/*  TP a pour but essentiel de montrer le principe de préemption du 	*/
/*  processeur. 							*/
/************************************************************************/
#include        <basec.h>
#include        <str.h>
#include        <video.h>

#define         T1      1
#define         T2      2
#define         T3      3
#define         TK      4

#define         PT1     1
#define         PT2     1
#define         PT3     1
#define         PTK     3

#define         Sem1            1
#define         ValMaxSem       1
#define         ESC                     0x1B

#define         AttInfinie      0L

Word            F0,F1,F2,F3,F4;
#include        "tempo.c"
/*-----------------------------------------------------*/
TKill(void)
{
Char car;
while(1)
	{
	LireCar(F1,ON,&car);
	if( car == ESC ) RetDos();
 }
}
/*-----------------------------------------------------*/
Tache1(void)
{
while(1)
	{
	EcrTexte(F1,"T111111\n");
	Tempo(10);
	EffaceFen(F1);
	P(Sem1,AttInfinie);
	}
}
/*-----------------------------------------------------*/
Tache2(void)
{
while(1)
	{
	EcrTexte(F2,"T222222\n");
	Tempo(10);
	EffaceFen(F2);
	V(Sem1);
	}
}
/*-----------------------------------------------------*/
Tache3(void)
{
while(1)
	{
	}
}
/*-----------------------------------------------------*/
void main(void)
{
InitVideo();

F0 = OuvreFen( 0, 0,79,24, noir, blanc, "EX 5a : SYNCHRONISATION AVEC UN SEMAPHORE BINAIRE (bis)");
F1 = OuvreFen(10,10,21,13, bleu, blanc, "EnCours");
F2 = OuvreFen(30, 3,41, 6, vert, blanc, "EnCours");
F3 = OuvreFen(50,10,61,13,rouge, blanc, "EnCours");
F4 = OuvreFen( 2,20,77,23, cyan, blanc, "TACHE MAIN");

InitNoyau();
CreateTask(T1, PT1, Tache1);
CreateTask(T2, PT2, Tache2);
CreateTask(T3, PT3, Tache3);
CreateTask(TK, PTK, TKill);
InitSemaphore(Sem1, ValMaxSem);

EnterRegion();
StartTask(T2);
StartTask(T1);
StartTask(TK);
LeaveRegion();

while(1)
	{
	EnterRegion();
	EcrCar(F4,'&');
	LeaveRegion();
	Tempo(2);
	}
}