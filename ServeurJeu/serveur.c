/**** Fichier principal pour le pont virtuel ****/

/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libreseau.h"
#include "libflux_execution.h"
#include "lib_protocole.h"

/** Quelques constantes **/

#define MAX_LIGNE     50
#define MAX_SERVICE   64
typedef struct SocketPort{ 
  int balise;
  unsigned short port;
}SocketPort;

//Gestion Client
void gestionClient(void *argument){

int s=*(int *)argument;
/* Obtient une structure de fichier */
FILE *dialogue=fdopen(s,"a+");
if(dialogue==NULL){ perror("gestionClient.fdopen"); exit(EXIT_FAILURE); }

/* Echo */
char ligne[MAX_LIGNE];
while(fgets(ligne,MAX_LIGNE,dialogue)!=NULL)
  fprintf(dialogue,"> %s",ligne);

/* Termine la connexion */
fclose(dialogue);

}
int gestion_client_leger(int dialogue){

  creat_task(gestionClient,&dialogue,sizeof(int));
  return 0;
}

void broadcast(void *argument)
{

  SocketPort  *Socket_Port=argument;
  int port=Socket_Port->port;
  int s=Socket_Port->balise;
 #ifdef DEBUG
fprintf(stdout,"je suis la %d\n",port);
#endif
  
  pr_udp_identite_t paqu_identite = {7,port,1800};
   
  pr_udp_identite_t *paqu_identite_ptr = &paqu_identite;
  char *hote="255.255.255.255";
  
  // unsigned char myMessage [] = "Serveur dispo, envoie un paquet pour avoir le paquet UDP de connexion";
  // unsigned char *message = &myMessage[0];
  char service[MAX_SERVICE];
  sprintf(service,"%d",port);
  void *adresse = creationAddresseUDP(hote,service);
  while (1)
  {
    envoyerUDP(s,adresse,paqu_identite_ptr,sizeof(paqu_identite_ptr));
    sleep(1);
  }
  
}

void gestionClientUDP(SocketPort info)
{
  creat_task(broadcast,&info,sizeof info);
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

// initialisation balise UDP

int balise;
balise=initialisationSocketUDP(service);

SocketPort Socket_Port;
Socket_Port.balise = balise;
Socket_Port.port=strtol(service,NULL,10) ;
// SocketPort *Socket_Port_ptr =&Socket_Port;
gestionClientUDP(Socket_Port);

int s;
// Initialisation du serveur

s=initialisationServeur(service,MAX_CONNEXIONS);
// Traitement des connexions et des messages
/* Lancement de la boucle d'ecoute */
boucleServeur(s,gestion_client_leger);

return 0;
}