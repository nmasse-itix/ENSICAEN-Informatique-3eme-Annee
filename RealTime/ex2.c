/************************************************************************/
/* EX2.C : Priorités                           	                    	*/
/************************************************************************/
/* Fonction :	               					    	*/
/*  On crée une tâche TK (TKill) de priorité 3 permettant de quitter	*/
/*  proprement une application.                                     	*/
/*  Puis une tâche T1 de priorité plus forte et une nouvelle fenêtre	*/
/*  dans laquelle cette tâche écrit en permanence.                   	*/
/*  Constater que TKill ne démarre pas.                              	*/
/*  Puis mettre à T1 une priorité moins forte et expliquer.          	*/
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define     T1	       1	/*Le numéro de la tâche Tache1 est 1*/
#define     TK	       2	/*Le numéro de la tâche TKill est 2*/
#define     PT	       3	/*La priorité de la tâche Tache1 est 2*/
#define     PTK        4	/*La priorité de la tâche TKill est 3*/
#define	    ESC        0x1b

Word F0,F1,F2;

#include "tempo.c"
/*--------------------------------------------------------------------*/
TKill(void)
{
Char car;

while(1)
	{
	LireCar(F1,ON,&car);
	if(car==ESC)
		{
		RetDos();
		}
	}
}
/*--------------------------------------------------------------------*/
Tache1(void)
{
while(1)
	{
	EcrTexte(F1,"T1111111");
	Tempo(5);
	EffaceFen(F1);
	Tempo(5);
	}
}
/*********************************************************************/
void main(void)
{
InitVideo();
F0 = OuvreFen( 0, 0,79,24, noir, blanc,"EXERCICE 2");
F1 = OuvreFen( 5, 5,20,10, bleu, blanc,"EnCours");
F2 = OuvreFen( 1,20,78,23, rouge,blanc,"TACHE MAIN");

InitNoyau();
CreateTask(T1, PT, Tache1);
CreateTask(TK, PTK,TKill);

EnterRegion();
StartTask(T1); /* Demarre T1 */
StartTask(TK); /* Demarre TK */
LeaveRegion();

while(1)
	{
	EcrCar(F2,'&');
	Tempo(2);
	}
}
