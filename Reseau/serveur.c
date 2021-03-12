/**** Fichier principal pour le pont virtuel ****/

/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "libreseau.h"
#include "libflux_execution.h"

/** Quelques constantes **/

/** Variables globales **/

/** Fonctions **/

// Boucle serveur
int boucleServeur(int ecoute,int (*traitement)(int))
{
int dialogue;

while(1){

    /* Attente d'une connexion */
    if((dialogue=accept(ecoute,NULL,NULL))<0) return -1;

    /* Passage de la socket de dialogue a la fonction de traitement */
    if(traitement(dialogue)<0){ shutdown(ecoute,SHUT_RDWR); return 0;}

    }
}


/* Fonction principale */
int main(int argc,char *argv[]){
// Analyse des arguments
if(argc!=2){
  fprintf(stderr,"Syntaxe : bridge <port>\n");
  exit(-1);
  }
char *service=argv[1];
#ifdef DEBUG
fprintf(stdout,"Port : %s\n",service);
#endif
int s;
// Initialisation du serveur

s=initialisationServeur(service,MAX_CONNEXIONS);
// Traitement des connexions et des messages
/* Lancement de la boucle d'ecoute */
boucleServeur(s,gestionClient);

return 0;
}