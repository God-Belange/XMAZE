
/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>

#include "libreseau.h"
#include "libgraph.h"
#include "lib_protocole.h"

/** Quelques constantes **/

#define MAX_SERVICE 1024
#define MAX_LIGNE 50
#define TITRE		"Interface Client"
#define LARGEUR		840
#define HAUTEUR		680

/** Variables globales */

struct sigaction action;
int socket_serveur;
int socket_chat;
int socket_touche;
char pseudo[10];

/** Fonctions **/

// envoie message pour le tchat

void envoie_tchat(char *message)
{
  write(socket_chat,message,strlen(message));   
}

void recevoir_tchat()
{
  char mes[MAX_LIGNE]="";
  if(read(socket_chat,mes,MAX_LIGNE)>0){
  printf("Vous avez récu un message : %s\n",mes);      
}

}

//  quitter le jeu 

void desincription(){

  char tampon[20]=CMD_ENDGAME;
  strcat(tampon, " ");
  strcat(tampon, pseudo);
  write(socket_serveur,tampon,strlen(tampon));               // se désincrire au serveur
	int octet;
  char ligne[MAX_LIGNE]="";
  if((octet=read(socket_serveur,ligne,MAX_LIGNE))>0){
    printf("%s\n",ligne);     
  }
  printf("Vous êtes déconnecté");
  shutdown(socket_serveur,SHUT_RDWR);
  shutdown(socket_chat,SHUT_RDWR);

}
// ctrl c pour quitter le jeu
void hand(int sig){
	if (sig == SIGINT){
		// Si SIG_INT
    desincription();   
		exit(SIGINT);
	} 
}

// demarrage du jeu et envoi de touche 

void demmarage_jeu(void *adresse_serveur,unsigned char id_client,char *port_touche){

  unsigned char resultat=creerFenetre(LARGEUR,HAUTEUR,TITRE);
  if(!resultat){ fprintf(stderr,"Problème graphique !\n"); exit(-1); }
  int touche;
  unsigned char fenetre,quitter;

  pr_udp_touches_t touche_udp;
  pr_udp_touches_t *touche_udpptr=&touche_udp;
  touche_udpptr->id_client= id_client;
  int balise;
  balise=initialisationSocketUDP(port_touche);
  void *adresse = creationAddresseUDP(adresse_serveur,port_touche);
  
  while(1){

    int evenement=attendreEvenement(&touche,&fenetre,&quitter);
    if(!evenement){ usleep(10000); continue; }
    if(touche)
    {
      touche_udpptr->touches=touche;
      envoyerUDP(balise,adresse,touche_udpptr,sizeof(touche_udpptr));
      if (quitter==1)desincription();
    }
  }
}

/* Fonction principale */
int main(int argc,char *argv[]){


  #ifdef DEBUG
  fprintf(stdout,"j attends un serveur\n");
  #endif

  pr_udp_identite_t mess;
  pr_udp_identite_t *messageptr = &mess;

  int balise;
  int chat;
  balise=initialisationSocketUDP(PORT_DIFFUSION_UDP);
  int octet;
  char ligne[MAX_LIGNE];
  void *adresse=NULL;
  while (1)                                               // j'attend le premier serveur disponible
  {
     int taille=sizeof(pr_udp_identite_t);
     adresse=recevoirUDP(balise, messageptr, &taille);
     if(taille>=(int)sizeof(pr_udp_identite_t)){
  #ifdef DEBUG
       printf("Sonde reçue port TCP serveur %hu\n",messageptr->port_tcp);
  #endif
       break; 
     }
  }

  char service[MAX_SERVICE];
  sprintf(service,"%d",messageptr->port_tcp);
  int s=connexionServeur(adresse,service);
  if(s>0)                                        // Si tout s'est passé lors de la connexion
  {

    socket_serveur=s;
    chat=connexionServeur(adresse,PORT_CHAT_TCP);

    if(chat<0)
    {
    #ifdef DEBUG
      fprintf(stderr,"Erreur de connexion au serveur chat\n"); exit(EXIT_FAILURE);
    #endif
    }

    socket_chat=chat;
    if((octet=read(s,ligne,MAX_LIGNE))>0) printf("%s\n",ligne);      
    fgets(pseudo, 10, stdin);
  }
  else
  {

    #ifdef DEBUG
      fprintf(stderr,"Erreur de connexion au serveur\n"); exit(EXIT_FAILURE);
    #endif 
  }

  char tampon[20]="pseudo ";
  strcat(tampon, pseudo);
  write(s,tampon,strlen(tampon));               // s'inscrire au serveur 
  char mes[MAX_LIGNE]="";
  if(read(s,mes,MAX_LIGNE)>0){
    printf("Vous êtes inscrit au serveur avec l' id %s\n",mes);      
  }
  // Fonction appelée par le signal
  action.sa_handler = hand;
  // Action sur réception SIGINT
  sigaction(SIGINT, &action, NULL);
  char message[MAX_LIGNE];
  while(1){ 

    printf("Taper votre message\n");
    fgets(message, MAX_LIGNE, stdin);
    envoie_tchat(message);                                     // test tchat

}

return 0;
}
