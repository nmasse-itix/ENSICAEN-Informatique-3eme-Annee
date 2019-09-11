/************************************************************************/
/*  EX5c.C      EVENEMENTS MULTIPLES                                    */
/************************************************************************/
/* Fonction :                                                           */
/*  Deux tâches de même priorité fonctionnent en partage du temps       */
/*  Une troisième tâche, de priorité plus forte doit effectuer un       */
/*  traitement demandé par l'une des tâches précédentes.                */
/* Principe :                                                           */
/*  Chacune des deux premières tâches signale son événement à la        */
/*  troisième tâche qui affichera un message correspondant à            */
/*  l'événement recu.                                                   */
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define T1      1
#define T2      2
#define T3      3
#define TK      4
#define PT1     1
#define PT2     1
#define PT3     2
#define PTK     3

#define SE1     0
#define SE2     1
#define WE1     0x01
#define WE2     0x02

#define ESC     0x1B


Word    F0,F1,F2,F3,F4;
#include "tempo.c"
/*--------------------------------------------------*/
TKill(void)
{
Char car;
LireCar(F4,ON,&car);
if( car == ESC ) RetDos();
}
/*--------------------------------------------------*/
Tache1(void)
{

while(1)
	{
	EcrTexte(F1,"\nSignale EVT1");
	Tempo(5);
	SignalEvent(T3,SE1);
	}
}
/*--------------------------------------------------*/
Tache2(void)
{
while(1)
	{
	EcrTexte(F2,"\nSignale EVT2");
	Tempo(5);
	SignalEvent(T3,SE2);
	}
}
/*--------------------------------------------------*/
Tache3(void)
{
Word events;
int cpt1 = 0, cpt2 = 0;
while(1)
	{
	   WaitEvents(WE1|WE2, 0, &events);

	   if (events&WE1)
	   {
		EffaceFen(F1);
		++cpt1;
		SelectFen(F3);
		EcrVar("EVT1 Recu (%d)\r", cpt1);
		ClearEvents(WE1);
	   }

	   if (events&WE2)
	   {
		EffaceFen(F2);
		++cpt2;
		SelectFen(F3);
		EcrVar("EVT2 Recu (%d)\r", cpt2);
		ClearEvents(WE2);
	   }
	}
}
/*--------------------------------------------------*/
void main(void)
{
InitVideo();

F0 = OuvreFen( 0, 0,79,24, noir, blanc, "EX 5c :EVENEMENTS MULTIPLES");
F1 = OuvreFen(10, 4,25, 7, vert, blanc, "Tache #1");
F2 = OuvreFen(55, 4,70, 7, bleu, blanc, "Tache #2");
F3 = OuvreFen(31, 7,49,19, rouge,blanc, "Tache #3");
F4 = OuvreFen( 2,20,77,23, cyan, blanc, "TACHE MAIN");

InitNoyau();
RTClockInit(1);
CreateTask(T1, PT1, Tache1);
CreateTask(T2, PT2, Tache2);
CreateTask(T3, PT3, Tache3);
CreateTask(TK, PTK, TKill);

EnterRegion();
StartTask(TK);
StartTask(T1);
StartTask(T2);
StartTask(T3);
LeaveRegion();

while(1)
	{
	EnterRegion();
	EcrCar(F4,'&');
	LeaveRegion();
	Tempo(2);
	}
}
