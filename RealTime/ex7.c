/************************************************************************/
/* EX7.C  IMPRIMANTE FICTIVE (mode caractère)				*/
/************************************************************************/
/* Fonction :								*/
/*  Une tâche productrice lit des caractères au clavier et les		*/
/*  transmet à une tâche consommatrice (à travers un buffer circulaire	*/
/*  commun) qui affiche ces caractères à vitesse lente (environ 2 carac-*/
/*  tères par seconde). Pour obtenir cette vitesse, la tâche consomma-  */
/*  teur se "suspend" pendant environ 0.5 seconde (DelayTask(10) )	*/
/*                                                                      */
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define	TP	1	/* Tâche Producteur */
#define	TC	2	/* Tâche Consommateur */

#define	PTP	3
#define	PTC     4

#define	TAILLE	5	/* Taille du buffer */
#define	ESC	0x1b


Word	F0,F1,F2,F3,F4,F5;

#include "tempo.c"

Char	Buffer[TAILLE];

Char 	posP = 0;
Char	posC = 0;
Char    ecriture = 0;





/*------------------------------------------------------------------*/
TacheProducteur(void)
{
Char car;
while(1)
	{
	/* Lecture d'un caractere */
	LireCar(F1,ON,&car);
	if(car == ESC) RetDos();

	/* Entree en section critique ? */
	if (posP == posC)
		{
		while (ecriture == 1)
			{
			/* On attend */
			EcrTexte(F4, "BUFFER PLEIN");
			DelayTask(1);
			EffaceFen(F4);
			}
		}

	/* Debut de la section critique (pas d'appel systeme) */
	Buffer[posP] = car;
	posP++;
	if (posP == TAILLE) posP = 0;
	ecriture = 1;
	/* Fin de la section critique */

	}
}
/*------------------------------------------------------------------*/
TacheConsommateur(void)
{
Char car;
while(1)
	{

	/* Entree en section critique ? */
	if (posP == posC)
		{
		while (ecriture == 0)
			{
			/* On attend */
			EcrTexte(F3, "Buffer vide");
			DelayTask(1);
			EffaceFen(F3);
			}
		}

	/* Debut de la section critique (pas d'appel systeme) */
	car = Buffer[posC];
	posC++;
	if (posC == TAILLE) posC = 0;
	ecriture = 0;
	/* Fin de la section critique */

	EcrCar(F2,car);
	DelayTask(10);
	}
}
/*------------------------------------------------------------------*/
void main(void)
{
InitVideo();
F0= OuvreFen( 0, 0,79,24,noir,blanc,"EXERCICE 7 : IMPRIMANTE FICTIVE (caractère + petit buffer)");
F1= OuvreFen( 2, 1,77, 8,bleu,blanc,"TACHE PRODUCTRICE (clavier)");
F2= OuvreFen( 2, 8,77,15,vert,blanc,"TACHE CONSOMMATEUR (imprimante)");
F3= OuvreFen( 2,16,22,19,magenta, blanc,"ATTENTION");
F4= OuvreFen(57,16,77,19,blanc,rouge,"ATTENTION");
F5= OuvreFen( 2,20,77,23,cyan,blanc,"TACHE MAIN");

EcrTexte(F3,"Buffer Vide");


InitNoyau();


CreateTask(TP,PTP,TacheProducteur);
CreateTask(TC,PTC,TacheConsommateur);

StartTask(TC);
StartTask(TP);

while(1)
	{
	EcrCar(F5,'&');
	Tempo(2);
	}
}
