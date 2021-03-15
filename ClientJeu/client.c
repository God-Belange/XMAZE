/**** Fichier principal pour le client du pont virtuel ****/

/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>

#include "libreseau.h"

#define MAX_NOM_INTERFACE 16
#define NOM_INTERFACE "tap0"

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
int s;

// Connexion au serveur
s=connexionServeur(serveur,service);
if(s<0){ fprintf(stderr,"Erreur de connexion au serveur\n"); exit(EXIT_FAILURE); } 
#ifdef DEBUG
	fprintf(stdout,"Connexion au serveur effectuée\n");
#endif   

// Ouverture de l'interface reseau
  // 	char interface[MAX_NOM_INTERFACE]=NOM_INTERFACE;
	// int fd=creationInterfaceVirtuelle(interface);
	// if(fd<0){
	// 	fprintf(stderr,"Erreur de la création d'une interface virtuelle\n");
	// 	exit(EXIT_FAILURE);
	// }
	// #ifdef DEBUG
	// fprintf(stdout,"Interface virtuelle créée\n");
	// #endif
// Communication avec le serveur

/* Boucle de communication avec le serveur */
struct pollfd descripteurs[2];
descripteurs[0].fd=s;
descripteurs[0].events=POLLIN;
descripteurs[1].fd=0;
descripteurs[1].events=POLLIN;
while(1){
  char tampon[MAX_CONNEXIONS];
  int nb=poll(descripteurs,2,-1);
  if(nb<0){ perror("main.poll"); exit(EXIT_FAILURE); }
  if((descripteurs[0].revents&POLLIN)!=0){
    int taille=read(s,tampon,MAX_CONNEXIONS);
    if(taille<=0) break;
    write(1,tampon,taille);
    }
  if((descripteurs[1].revents&POLLIN)!=0){
    int taille=read(0,tampon,MAX_CONNEXIONS);
    if(taille<=0) break;
    write(s,tampon,taille);
    }
  }
/* On termine la connexion */
shutdown(s,SHUT_RDWR);

return 0;
}