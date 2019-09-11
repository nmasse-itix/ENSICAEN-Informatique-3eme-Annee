/************************************************************************/
/* EX7A.C  IMPRIMANTE FICTIVE (mode ligne)				*/
/************************************************************************/
/* Fonction :								*/
/*  Une tache productrice lit des lignes de caractères terminées    	*/
/*  par un RC. Dés qu'une ligne a été saisie elle le signale à une  	*/
/*  tâche de consommation qui affiche les caractères à vitesse lente.	*/
/*  Cette vitesse, 2 caractères par secondes, est contrôlée par Tempo(5)*/
/*  ou DelayTask(10).                                                   */
/*  Le passage se fait à travers un buffer circulaire commun. 		*/
/*  La taille du buffer circulaire est sur dimensionnée : on ne se 	*/
/*  pose pas le problème d'un éventuel débordement du buffer.		*/
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define	TP	1	/* Tâche Producteur */
#define	TC	2	/* Tâche Consommateur */

#define	PTP	3
#define	PTC     4


#define MB	1
#define MB_LEN	16

#define	TAILLE	100	/* Taille du buffer */
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
Int numChar = 0;
while(1)
	{
	/* Lecture d'un caractere */
	LireCar(F1,ON,&car);

	if(car == ESC) RetDos();

	if (car == '\r')
		{
		Send(MB, numChar);
		numChar = 0;
		}
	else
		{
		/* Entree en section critique ? */
		if (posP == posC && ecriture == 1)
			{
			/* Buffer plein, on oublie le caractere */
			EcrTexte(F5, "\nBUFFER PLEIN");
			}
		else
			{
			/* Debut de la section critique (pas d'appel systeme) */
			Buffer[posP] = car;
			posP++;
			if (posP == TAILLE) posP = 0;
			ecriture = 1;
			++numChar;
			/* Fin de la section critique */
			}
		}
	}
}
/*------------------------------------------------------------------*/
TacheConsommateur(void)
{
Char car;
Int numChar;
while(1)
	{

	/* Attente de fin de ligne */
	Receive(MB, &numChar, 0);

	/* Le buffer va etre desempli */
	EffaceFen(F5);

	while (numChar --)
		{
		car = Buffer[posC];
		posC++;
		if (posC == TAILLE) posC = 0;
		ecriture = 0;

		EcrCar(F2,car);
		DelayTask(10);
		}
	EcrCar(F2, '\r');
	}
}


/*------------------------------------------------------------------*/
void main(void)
{
InitVideo();
F0= OuvreFen( 0, 0,79,24,noir,blanc,"EXERCICE 7A : IMPRIMANTE FICTIVE (ligne + grand buffer)");
F1= OuvreFen( 2, 1,77, 8,bleu,blanc,"TACHE PRODUCTRICE (clavier)");
F2= OuvreFen( 2, 8,77,15,vert,blanc,"TACHE CONSOMMATEUR (imprimante)");
F3= OuvreFen( 2,20,77,23,cyan,blanc,"TACHE MAIN");
F4= OuvreFen( 2,16,22,19,magenta, blanc,"ATTENTION");
F5= OuvreFen(57,16,77,19,blanc,rouge,"ATTENTION");

InitNoyau();
CreateTask(TP,PTP,TacheProducteur);
CreateTask(TC,PTC,TacheConsommateur);


InitMailBox(MB, MB_LEN);

EnterRegion();
StartTask(TP);
StartTask(TC);
LeaveRegion();

while(1)
	{
	EcrCar(F3,'&');
	Tempo(2);
	}
}
