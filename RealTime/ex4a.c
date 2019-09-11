/************************************************************************/
/* EX4A.C : Round-Robin avec protection des Ressources                   */
/************************************************************************/
/* Fonction :                                                           */
/*  Quatre tâches de même priorité travaillent SANS partage du temps    */
/*  Ces quatre tâches utilisent une fenêtre commune pour afficher       */
/*  leur message.                                                       */
/* Principe :                                                           */
/*  La ressource commune est protegée par un sémaphore binaire          */
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define T1      1
#define T2      2
#define T3      3
#define T4      4
#define TK      5
#define PT      1
#define PTK     2
#define ESC     0x1B

#define Sem             1
#define ValMaxSem       1

Word    F0,F1,F2;

#include "tempo.c"

/*-----------------------------------------------*/
TKill(void)
{
Char car;
while(1)
	{
	LireCar(F2,ON,&car);
	if(car==ESC)
		{
		RetDos();
		}
	}
}
/*-----------------------------------------------*/
Tache1(void)
{
P(Sem,0); /*Blocage initial des taches (synchronisation)*/
while(1)
	{
	EcrTexte(F2,"T11111");
	Tempo(5);
	EffaceFen(F2);
	P(Sem,0); /*Remise de la tache dans la file d'attente du semaphore*/
	}
}
/*-----------------------------------------------*/
Tache2(void)
{
P(Sem,0);
while(1)
	{
	EcrTexte(F2,"T22222");
	Tempo(5);
	EffaceFen(F2);
	P(Sem,0);
	}
}
/*-----------------------------------------------*/
Tache3(void)
{
P(Sem,0);
while(1)
	{
	EcrTexte(F2,"T33333");
	Tempo(5);
	EffaceFen(F2);
	P(Sem,0);
	}
}
/*-----------------------------------------------*/
Tache4(void)
{
P(Sem,0);
while(1)
	{
	EcrTexte(F2,"T44444");
	Tempo(5);
	EffaceFen(F2);
	P(Sem,0);
	}
}
/*-----------------------------------------------*/
void main(void)
{
InitVideo();
F0 = OuvreFen( 0, 0,79,24, noir, blanc,"EX 4 : Round Robin et Sémaphore");
F1 = OuvreFen( 2,20,77,23, cyan, blanc,"TACHE MAIN");
F2 = OuvreFen( 5,10,20,15, bleu, blanc,"EnCours");

InitNoyau();

/* NOTE : Dans cet example on n'utilise pas le temps partage */

CreateTask(T1, PT, Tache1);
CreateTask(T2, PT, Tache2);
CreateTask(T3, PT, Tache3);
CreateTask(T4, PT, Tache4);
CreateTask(TK, PTK,TKill);


InitSemaphore(Sem, ValMaxSem); /*Creation du semaphore*/
/* On n'initialise pas le semaphore ici (cf. plus bas)*/


/*Ici on n'a pas besoin de section critique car T1, T2, T3 et T4 seront*/
/*bloquees sur la prise de semaphore et TK sera bloque sur la lecture du*/
/*clavier. De cette maniere la tache main pourra continuer a s'executer.*/
/*T1, T2, T3 et T4 seront inserees de maniere ordonnee dans la file*/
/*d'attente du semaphore*/

StartTask(T1); /*Demarrage des taches*/
StartTask(T2);
StartTask(T3);
StartTask(T4);
StartTask(TK);

Tempo(10); /*Laisse le temps a l'ecran LCD de changer de mode video*/

/*On debloque la premiere tache de la file d'attente du semaphore*/
V(Sem);

while(1)
	{
	EcrCar(F1,'&');
	V(Sem);         /*Lorsque toutes les taches sont bloques on debloque la suivante dans la file d'attente*/
	}
}
