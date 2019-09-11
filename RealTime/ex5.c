/************************************************************************/
/* EX5.C : Synchronisation par événements                               */
/************************************************************************/
/* Fonction :                                                           */
/*  Trois tâches de même priorité doivent afficher "circulairement"     */
/*  un message dans leur fenêtre respective.                            */
/*  Ces trois tâches se synchronisent mutuellement.                     */
/* Principe :                                                           */
/*  La synchronisation est réalisée par des évenemets : chacune des     */
/*  tâches attend de la tâche précédente un évenement puis signale      */
/*  un évenement a la suivante.                                         */
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define T1      1
#define T2      2
#define T3      3
#define TK      4
#define PT      1
#define PTK     2

#define SE1     0       /* On peut prendre n'importe quelle valeur < 16 */
#define SE2     1       /* On peut prendre n'importe quelle valeur < 16 */
#define SE3     15      /* On peut prendre n'importe quelle valeur < 16 */

#define WE1     0x0001
#define WE2     0x0002
#define WE3     0x8000

#define ESC     0x1B

Word    CopieEvtSig;

Word    F0,F1,F2,F3,F4;

#include "tempo.c"
/*---------------------------------------------*/
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
/*---------------------------------------------*/
Tache1(void)
{
while(1)
	{
	EcrTexte(F1,"T11111");
	Tempo(10);
	EffaceFen(F1);
	ClearEvents(WE1);
	SignalEvent(T2,SE2);
	WaitEvents(WE1, 0, &CopieEvtSig);
	}
}
/*---------------------------------------------*/
Tache2(void)
{
while(1)
	{
	EcrTexte(F2,"T22222");
	Tempo(10);
	EffaceFen(F2);
	ClearEvents(WE2);
	SignalEvent(T3,SE3);
	WaitEvents(WE2, 0, &CopieEvtSig);
	}
}
/*---------------------------------------------*/
Tache3(void)
{
while(1)
	{
	EcrTexte(F3,"T33333");
	Tempo(10);
	EffaceFen(F3);
	ClearEvents(WE3);
	SignalEvent(T1,SE1);
	WaitEvents(WE3, 0, &CopieEvtSig);
	}
}
/*---------------------------------------------*/
void main(void)
{
InitVideo();

F0 = OuvreFen( 0, 0,79,24, noir, blanc,"EX 5 : SYNCHRONISATION PAR EVENEMENTS");
F1 = OuvreFen(10,10,21,13, bleu, blanc, "EnCours");
F2 = OuvreFen(30, 3,41, 6, vert, blanc, "EnCours");
F3 = OuvreFen(50,10,61,13, rouge,blanc, "EnCours");
F4 = OuvreFen( 2,20,77,23, cyan, blanc, "TACHE MAIN");


InitNoyau();
CreateTask(T1, PT, Tache1);
CreateTask(T2, PT, Tache2);
CreateTask(T3, PT, Tache3);
CreateTask(TK, PTK, TKill);

EnterRegion();
StartTask(T3);
StartTask(T2);
StartTask(T1);
StartTask(TK);
LeaveRegion();

while(1)
	{
	EcrCar(F4,'&');
	Tempo(2);
	}
}
