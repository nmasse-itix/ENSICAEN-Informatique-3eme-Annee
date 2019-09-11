/********************************************************************/
/* EX3.C : EnterRegion et LeaveRegion                               */
/*         Primitive de partage du temps RTClockInit()              */
/********************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define	T1	1	/* La tâche Tache1 a le numéro 1 */
#define	T2	2	/* La tâche Tache2 a le numéro 2 */
#define	TK	3	/* La tâche TKill  a le numéro 3 */
#define	PT1	2	/* La tâche numéro 1 a la priorité 2 */
#define	PT2	2   	/* La tâche numéro 2 a aussi la priorité 2 */
#define	PTK	3	/* La tâche numéro 3 a la priorité 3 : c'est elle la plus prioritaire */
#define	ESC	0x1b

Word F0,F1,F2,F3;

#include "tempo.c"
/*-------------------------------------------------------------------*/
TKill()
{
Char car;
while (1)
	{
	LireCar(F1,ON,&car);
	if(car==ESC)
		{
		RetDos();
		}
	}
}
/*-------------------------------------------------------------------*/
Tache1()
{
while(1)
	{
	EcrTexte(F1,"T1111111");
	Tempo(5);
	EffaceFen(F1);
	Tempo(5);
	}
}

/*-------------------------------------------------------------------*/
Tache2()
{
while(1)
	{
	EcrTexte(F2,"T2222222");
	Tempo(5);
	EffaceFen(F2);
	Tempo(5);
	}
}
/*-------------------------------------------------------------------*/
void main(void)
{
InitVideo();
F0 = OuvreFen( 0, 0,79,24, noir, blanc,"EXERCICE 3");
F1 = OuvreFen( 5, 5,20,10, bleu, blanc,"T1 EnCours");
F2 = OuvreFen(25, 5,40,10, vert, blanc,"T2 EnCours");
F3 = OuvreFen( 1,20,78,23, rouge,blanc,"TACHE MAIN");

InitNoyau();
CreateTask(T1, PT1, Tache1);
CreateTask(T2, PT2, Tache2);
CreateTask(TK, PTK, TKill);


EnterRegion(); /*La section critique permet de demarrer toutes les taches*/

StartTask(TK); /*En changeant l'ordre des taches, on arrive a lancer T1 et TK mais pas T2*/
StartTask(T1);
StartTask(T2); /*T1 et T2 ont la meme priorite. Seule la derniere tache demarree est prise en compte (ici T2)*/

LeaveRegion();


while(1)
	{
	EcrCar(F3,'&');
	Tempo(2);
	}
}
