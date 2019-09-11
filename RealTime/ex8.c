/************************************************************************/
/*  EX8.C       RESSOURCES MULTIPLES                                    */
/************************************************************************/
/* Fonction :                                                           */
/*  N tâches utilisent M ressources identiques (M < N).                 */
/*  Lorsque une tâche demande une ressource, la première ressource      */
/*  disponible lui est attribuée. Si aucune ressource n'est             */
/*  disponible alors la tâche est suspendue.                            */
/* Principe :                                                           */
/*  Les ressources sont constituées par des fenêtres.                   */
/*  Une tâche ayant obtenu une ressource y affiche son message puis     */
/*  libère la ressource.                                                */
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define T1      1
#define T2      2
#define T3      3
#define T4      4
#define T5      5
#define T6      6

#define TK      7

#define PT      1
#define PTK     3

#define MB	1
#define RES	3 /* nombre de ressources*/

#define ESC     0x1b

Word    F0,F1,F2,F3,F4;

Char	res[RES];

#include "tempo.c"
/*--------------------------------------------------------------------*/
TKill(void)
{
Char car;
while (1)
	{
	LireCar(F4, OFF, &car);
	if (car == ESC) RetDos();
	if (car == ' ')
		{
		StopTask(T1);
		StopTask(T2);
		StopTask(T3);
		StopTask(T4);
		StopTask(T5);
		StopTask(T6);
		LireCar(F4, OFF, &car);
		RetDos();
		}
	}
}
/*--------------------------------------------------------------------*/
Tache1(void)
{
Char f;
while (1)
	{
	Receive(MB,&f,0); 	/*Attente d'une ressource*/
	EcrTexte(res[f],"Tache1\r");
	Tempo(5);
	Send(MB,f);		/*Liberation de la ressource*/
	}
}
/*--------------------------------------------------------------------*/
Tache2(void)
{
Char f;
while (1)
	{
	Receive(MB,&f,0);
	EcrTexte(res[f],"Tache2\r");
	Tempo(5);
	Send(MB,f);
	}
}
/*--------------------------------------------------------------------*/
Tache3(void)
{
Char f;
while (1)
	{
	Receive(MB,&f,0);
	EcrTexte(res[f],"Tache3\r");
	Tempo(5);
	Send(MB,f);
	}
}
/*--------------------------------------------------------------------*/
Tache4(void)
{
Char f;
while (1)
	{
	Receive(MB,&f,0);
	EcrTexte(res[f],"Tache4\r");
	Tempo(5);
	Send(MB,f);
	}
}
/*--------------------------------------------------------------------*/
Tache5(void)
{
Char f;
while (1)
	{
	Receive(MB,&f,0);
	EcrTexte(res[f],"Tache5\r");
	Tempo(5);
	Send(MB,f);
	}
}
/*--------------------------------------------------------------------*/
Tache6(void)
{
Char f;
while (1)
	{
	Receive(MB,&f,0);
	EcrTexte(res[f],"Tache6\r");
	Tempo(5);
	Send(MB,f);
	}
}
/*--------------------------------------------------------------------*/
void main(void)
{
InitVideo();

F0 = OuvreFen( 0, 0,79,24, noir, blanc, "EX 8 : RESSOURCES MULTIPLES");
F1 = OuvreFen(20, 1,30,20, rouge,blanc, "Ress1");
F2 = OuvreFen(35, 1,45,20, bleu, blanc, "Ress2");
F3 = OuvreFen(50, 1,60,20, vert, blanc, "Ress3");
F4 = OuvreFen( 2,20,77,23, cyan, blanc, "MAIN");

InitNoyau();

/* Temps partage */
RTClockInit(1);

CreateTask(T1, PT, Tache1);
CreateTask(T2, PT, Tache2);
CreateTask(T3, PT, Tache3);
CreateTask(T4, PT, Tache4);
CreateTask(T5, PT, Tache5);
CreateTask(T6, PT, Tache6);
CreateTask(TK, PTK, TKill);

InitMailBox(MB,RES);

/* Les ressources */
res[0] = F1;
res[1] = F2;
res[2] = F3;

/* Mise a disposition des ressources */
Send(MB,0);
Send(MB,1);
Send(MB,2);

EnterRegion();
StartTask(TK);
StartTask(T1);
StartTask(T2);
StartTask(T3);
StartTask(T4);
StartTask(T5);
StartTask(T6);
LeaveRegion();


while(1)
	{
	EcrCar(F4,'&');
	Tempo(2);
	}
}
