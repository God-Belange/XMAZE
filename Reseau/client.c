/**** Fichier principal pour le client du pont virtuel ****/

/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "libreseau.h"

/** Quelques constantes **/

/** Variables globales */

/** Fonctions **/

/* Fonction principale */
int main(int argc,char *argv[]){
// Analyse des arguments
if(argc!=3){
  fprintf(stderr,"Syntaxe : client <serveur> <port>\n");
  exit(-1);
  }
char *serveur=argv[1];
char *service=argv[2];
#ifdef DEBUG
fprintf(stdout,"Pont sur %s port %s\n",serveur,service);
#endif

// Connexion au serveur

// Ouverture de l'interface reseau

// Communication avec le serveur

return 0;
}