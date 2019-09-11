/************************************************************************/
/*  EX6.C : Communication par Boîte à Lettres                           */
/************************************************************************/
/* Fonction :                                                           */
/*  Une première tâche lit des caractères au clavier puis les           */
/*  communique à une seconde tâche qui affiche le caractère reçu.       */
/*  Si aucun caractère n'est reçu au bout d'un certain temps, la        */
/*  tache de réception affiche un message d'erreur.                     */
/* Principe :                                                           */
/*  La tâche de consommation lit la boîte à lettres avec un time-out.   */
/*  Si la boîte est remplie avant l'expiration du time-out:             */
/*     Alors lire le caractère puis l'afficher.                         */
/*     Sinon afficher "Time-Out" dans une troisième fenêtre.            */
/*  FinSi                                                               */
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define T1      1       /*TacheProducteur*/
#define T2      2       /*TacheConsommateur*/

#define PT1     4       /*Priorité TacheProducteur*/
#define PT2     3       /*Priorité TacheConsommateur*/

#define BL      1       /*On utilise une boîte à lettres...*/
#define TBL     1       /*... de taille 1*/
#define TOBL    20      /*... avec un time out de 2 secondes*/
#define ESC     0x1b

Word    F0,F1,F2,F3,F4;

#include "tempo.c"
/*-------------------------------------------------------------------*/
TacheProducteur()
{
Char car;
while(1)
	{
	LireCar(F1,ON,&car);
	if (car == ESC) RetDos();
	Send(BL,car);
	}
}
/*-------------------------------------------------------------------*/
TacheConsommateur()
{
Char car;
while(1)
	{
	if(Receive(BL,&car,TOBL))
		{
		EcrTexte(F4, "Time-out");
		Tempo(10);
		EffaceFen(F4);
		}
	else
		{
		EcrCar(F2,car);
		}
	}
}
/*-------------------------------------------------------------------*/
void main(void)
{
InitVideo();
F0 = OuvreFen( 0, 0,78,24, noir, blanc, "EXERCICE 6 : Communication par BL");
F1 = OuvreFen( 5,10,25,15, vert, blanc, "Producteur");
F2 = OuvreFen(45,10,65,15, bleu, blanc, "Consommateur");
F4 = OuvreFen(45,16,65,19, bleu, blanc, "Time-out");
F3 = OuvreFen( 2,20,77,23, cyan ,blanc, "TACHE MAIN");

InitNoyau();

InitMailBox(BL, TBL);

CreateTask(T1, PT1, TacheProducteur);
CreateTask(T2, PT2, TacheConsommateur);

EnterRegion();
StartTask(T1);
StartTask(T2);
LeaveRegion();

while(1)
	{
	EcrCar(F3,'&');
	Tempo(2);
	}
}