/*******************************/
/* Boucle d'attente logicielle */
/*******************************/
void Tempo(unsigned int Duree)
{
char *ret_getenv;
unsigned int delay;
unsigned long n2;

ret_getenv=getenv("TEMPO");
if( ret_getenv[0] == 0 )
	{
	printf("LA VARIABLE ENVIRONNEMENT TEMPO N'EST PAS DEFINIE\n\007");
	while(1);
	}

sscanf(ret_getenv,"%d",&delay);


while( Duree-- != 0 )
	{
	n2=(unsigned long)(delay) << 9;
	while( --n2 != 0 );
	}
}
