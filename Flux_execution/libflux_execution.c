#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libflux_execution.h"

#define MAX_LIGNE 50

//Gestion Client
int gestionClient(int s){

/* Obtient une structure de fichier */
FILE *dialogue=fdopen(s,"a+");
if(dialogue==NULL){ perror("gestionClient.fdopen"); exit(EXIT_FAILURE); }

/* Echo */
char ligne[MAX_LIGNE];
while(fgets(ligne,MAX_LIGNE,dialogue)!=NULL)
  fprintf(dialogue,"> %s",ligne);

/* Termine la connexion */
fclose(dialogue);
return 0;
}