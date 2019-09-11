/************************************************************************/
/* EX10.C               DEMONSTRATION TACHE SERVEUR                     */
/************************************************************************/
/* Fonction :                                                           */
/*  Deux tâches T1 et T2, de même priorité transmettent à une tâche     */
/*  serveur, TS, des requêtes pour utiliser une ressource (fenêtre)     */
/*  gérée par cette tâche TS.                                           */
/*  Ces requêtes, effectuées de manière "pseudo aléatoire", sont        */
/*  servies suivant leur ordre d'arrivée (fonctionnement asynchrone).   */
/* Principe :                                                           */
/*  Les tâches demandeuses T1 et T2 postent dans la file serveur des    */
/*  caractères minuscules (T1) ou majuscules (T2).                      */
/*  La tâche serveur TS affiche les caractères contenus dans la file.   */
/************************************************************************/
#include <basec.h>
#include <str.h>
#include <video.h>

#define T1      1
#define T2      2
#define TS      3
#define TK      4


#define T1DMAX  20
#define T1DSTEP 2
#define T2DMAX  20
#define T2DSTEP	4

#define PT      3       /* Priorité des tâches T1 et T2 */
#define PS      4        /* Priorité de la tâche serveur TS*/
#define PTK     5

#define BL      1       /*On utilise une boîte à lettres (boîte numéro 1)*/
#define BL_LEN	2


#define ESC     0x1b

Word    F0,F1,F2,F3,F4;

#include "tempo.c"
/*-------------------------------------------------------------------*/
TKill(void)
{
Char car;
while (1)
	{
	LireCar(F4, ON, &car);
	if (car == ESC) RetDos();
	}
}


/*-------------------------------------------------------------------*/
Tache1(void)
{
Char lettre = 'a';
Word delai1 = T1DSTEP;

while(1)
	{
	EcrCar(F1, lettre);
	Send(BL,lettre);
	++lettre;
	if (lettre > 'z') lettre = 'a';
	DelayTask(delai1);
	delai1 += T1DSTEP;
	if (delai1 > T1DMAX) delai1 = T1DSTEP;
	}
}
/*-------------------------------------------------------------------*/
Tache2(void)
{
Char lettre = 'A';
Word delai1 = T2DSTEP;

while(1)
	{
	EcrCar(F2, lettre);
	Send(BL,(Word)lettre);
	++lettre;
	if (lettre > 'Z') lettre = 'A';
	DelayTask(delai1);
	delai1 += T2DSTEP;
	if (delai1 > T2DMAX) delai1 = T2DSTEP;
	}
}

/*-------------------------------------------------------------------*/
Serveur(void)
{
Word msg;
while(1)
	{
	Receive(BL,&msg,0);
	EcrCar(F3, (char) msg);
	}
}
/*-------------------------------------------------------------------*/
void main(void)
{
InitVideo();

F0 = OuvreFen( 0, 0,79,24, noir,  blanc, "EX 10 : TACHE SERVEUR");
F1 = OuvreFen(10, 3,35,10, vert,  blanc, "TACHE T1");
F2 = OuvreFen(45, 3,70,10, vert,  blanc, "TACHE T2");
F3 = OuvreFen(10,11,70,16, rouge, blanc, "Serveur (TACHE TS)");
F4 = OuvreFen( 2,20,77,23, cyan,  blanc, "TACHE MAIN");

InitNoyau();
InitMailBox(BL, BL_LEN);


CreateTask(TK, PTK, TKill);
CreateTask(T1, PT, Tache1);
CreateTask(T2, PT, Tache2);
CreateTask(TS, PS, Serveur);


StartTask(TK);
StartTask(TS);
StartTask(T1);
StartTask(T2);


while(1)
	{
	EcrCar(F4,'&');
	Tempo(2);
	}
}
