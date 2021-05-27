/**** Fichier principal pour le client du pont virtuel ****/

/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>

#include "libreseau.h"
#include "lib_protocole.h"

#define MAX_NOM_INTERFACE 16
#define NOM_INTERFACE "tap0"

/** Quelques constantes **/

/** Variables globales */

/** Fonctions **/
typedef struct SocketPort{ 
  int balise;
  unsigned short port;
}SocketPort;

int s;

void client_listenUDP()
{

#ifdef DEBUG
fprintf(stdout,"j attends un serveur\n");
#endif

//char *serveur="192.168.19.129";
pr_udp_identite_t *message;

char *service="1500";

int balise;
balise=initialisationSocketUDP(service);

//void *serveur = recevoirUDP(balise, &message, sizeof(&message));
void *serveur;

char flag = 0;
//trouve = 0;

while (flag == 0) // Tant qu'on a rien on écoute le réseau
{

  serveur = recevoirUDP(balise, &message, sizeof(&message));

    /*#ifdef DEBUG
    fprintf(stdout,"Pont sur %s port %s\n",serveur,service);
    #endif*/
  //if(trouve == 1) // Variable géré par la fonction recevoirUDP (permet de dire si on a trouvé quelque chose)
  //{
    s=connexionServeur(serveur,service);
    if(s == 4) // Si tout s'est passé lors de la connexion
    {
      flag = 1; // On a trouvé un serveur
      trouve = 0;

      #ifdef DEBUG
        fprintf(stdout,"Connexion au serveur effectuée \n");
      #endif 
    }
    if(s<0){ fprintf(stderr,"Erreur de connexion au serveur\n"); exit(EXIT_FAILURE);}
  //}

}
/*unsigned char *message;//pr_udp_identite_t *message;
struct sockaddr_storage  adresse;
unsigned char flag = 0;
  
while (flag == 0) // Tant qu'on a rien on écoute le réseau
{
  adresse = recevoirUDP(s, *message, sizeof(message));
  
  //if(adresse != NULL)//recevoirUDP(Socket_Port, *message, sizeof(message))){//adresse) 
  //{
    //flag = 1;

  #ifdef DEBUG
    fprintf(stdout,"BI");
  #endif
    // Connexion au serveur
  s=connexionServeur(adresse,1500);
  if(s<0){ fprintf(stderr,"Erreur de connexion au serveur\n"); exit(EXIT_FAILURE); }
  else 
  {
    flag = 1;

    #ifdef DEBUG
      fprintf(stdout,"Connexion au serveur effectuée\n");
    #endif
  } 
    
  };

  sleep(1);
}*/
}

/* Fonction principale */
int main(int argc,char *argv[]){
// Analyse des arguments
/*if(argc!=3){
  fprintf(stderr,"Syntaxe : client <serveur> <port>\n");
  exit(-1);
  }*/

client_listenUDP();

//char *serveur=argv[1];
//char *service=argv[2];

  

/* Boucle de communication avec le serveur */
/*struct pollfd descripteurs[2];
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
  }*/
/* On termine la connexion */
shutdown(s,SHUT_RDWR);

return 0;
}