/************************************************************************/
/* EX9.C                        TACHE CYCLIQUE                          */
/************************************************************************/
/* Fonction :                                                           */
/*   Une tâche TacheCyclique devant exécuter un traitement périodique   */
/*   est mise en exécution cycliquement.                                */
/* Principe:                                                            */
/*   Une tâche BaseDeTemps signale régulièrement un événement à la      */
/*   tâche TacheCyclique.                                               */
/*   La tâche TacheCyclique se met en attente de cet événement,         */
/*   puis fait son traîtement, puis attend à nouveau l'événement ...    */
/*   L'avantage est qu'ici la périodicité du traitement ne dépend       */
/*   pas de la durée de celui-ci.                                       */
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define TC      1       /* TacheCyclique */
#define TBDT    2       /* BaseDeTemps */
#define TK      3       /* TKill */

#define PTC     4        /* Priorité TacheCyclique */
#define PBDT    5        /* Priorité BaseDeTemps */
#define PTK     3        /* Priorité TKill */

#define EVT	0
#define MEVT    1
#define DELAY	20

#define ESC     0x1b

Word    F0,F1,F2,F3;

#include "tempo.c"
/*--------------------------------------------------------------------*/
TKill(void)
{
while(1)
	{
	Char car;
	LireCar(F1, ON, &car);
	if (car == ESC) RetDos();
	}
}
/*--------------------------------------------------------------------*/
BaseDeTemps(void)
{
while(1)
	{
	SignalEvent(TC, EVT);
	DelayTask(DELAY);
	}
}
/*--------------------------------------------------------------------*/
TacheCyclique(void)
{
while(1)
	{
	Word evt;
	WaitEvents(MEVT, 0, &evt);
	F2 = OuvreFen(50, 5,70,10, rouge, blanc, "TACHE CYCLIQUE");
	Tempo(5);
	FermeFen(F2);
	ClearEvents(evt);
	}
}
/*--------------------------------------------------------------------*/
void main(void)
{
InitVideo();

F0 = OuvreFen( 0, 0,79,24,noir, blanc, "EX9 : TACHE CYCLIQUE");
F1 = OuvreFen( 5, 5,40,15,bleu, blanc, "TACHE TKill");
F3 = OuvreFen( 2,20,77,23,cyan, blanc, "TACHE MAIN");

InitNoyau();

CreateTask(TK, PTK, TKill);
CreateTask(TC, PTC, TacheCyclique);
CreateTask(TBDT, PBDT, BaseDeTemps);

EnterRegion();
StartTask(TK);
StartTask(TC);
StartTask(TBDT);
LeaveRegion();

/* A compléter */
while(1)
	{
	EcrCar(F3,'&');
	Tempo(2);
	}
}
