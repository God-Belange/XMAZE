/**** Fichier principal pour le pont virtuel ****/

/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "libreseau.h"
#include "libflux_execution.h"
#include "lib_protocole.h"
#include "libgestion_list.h"

/** Quelques constantes **/

#define MAX_SERVICE   64
#define MAX_LENGTH    10


ListClient list;
int id_client;


/** Gestion clients 
   ________________**/

void gestionClient(void *argument){

int s=*(int *)argument;
/* Obtient une structure de fichier */
FILE *dialogue=fdopen(s,"a+");
if(dialogue==NULL){ perror("gestionClient.fdopen"); exit(EXIT_FAILURE); }
 char message[80];
  sprintf(message, "Inscrivez vous en envoyant votre pseudo\n ");
  fputs(message,dialogue);
/* Echo */
char ligne[MAX_LIGNE];
while(fgets(ligne,MAX_LIGNE,dialogue)!=NULL){ 
   // fprintf(dialogue,"> %s\n",ligne);

    char delimit[] = " ";
    char* token = NULL;
    char *ptr = ligne;
    Client client;
    char ligne1[MAX_LIGNE];
    char ligne2[MAX_LIGNE];

    token = strtok(ptr, delimit);
    if (token != NULL){ 
        for (unsigned int i = 0; i < strlen(token); i++) {
         ligne1[i]=token[i];
        }
        token = strtok(NULL, delimit);
        if(token!=NULL){ 
            for (unsigned int u = 0; u < strlen(token); u++) {
            ligne2[u]=token[u];
            }
            if(strcmp(ligne1,CMD_CONNECTION)==0){ 

              strcpy(client.pseudo,ligne2);
              id_client++;
              client.socket=s;
              sprintf(client.id,"%d",id_client);

              if(add_Client_to_list(&list,client)==true){
                char input[MAX_LIGNE];
                sprintf(input, "idclient %d\n", id_client);
                fputs(input,dialogue);
              }else fprintf(dialogue,"> Vous etes déjà inscrit\n");

            }else if (strcmp(ligne1,CMD_ENDGAME)==0){

              strcpy(client.pseudo,ligne2);
              if(delete_Client_to_list(&list,client)==true){
                char message[80];
                sprintf(message, "Le pseudo %s a ete supprime\n ", client.pseudo);
                fputs(message,dialogue);
              }

            }
          }else  fprintf(dialogue,"> Format Commande erroné\n");
    }else fprintf(dialogue,"> Format Commande erroné\n"); 
   display_Client_list(list);
}


  

/* Termine la connexion */
fclose(dialogue);

}
int gestion_client_leger(int dialogue){

  creat_task(gestionClient,&dialogue,sizeof(int));
  return 0;
}


/** Gestion UDP broadcast 
   ________________**/

void broadcast(void *argument)
{

  SocketPort  *Socket_Port=argument;
  int port=Socket_Port->port;
  int s=Socket_Port->balise;
  
  pr_udp_identite_t paqu_identite = {7,port,PORT_TOUCHES_UDP};
   
  pr_udp_identite_t *paqu_identite_ptr = &paqu_identite;
  char *hote="255.255.255.255";
  
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

/** Gestion Serveur chat 
   ________________**/


void envoieChat(int s,char * message){
  write(s,message,strlen(message));
}

void gestionChat(void *argument){

int s=*(int *)argument;
/* Obtient une structure de fichier */
FILE *dialogue=fdopen(s,"a+");
if(dialogue==NULL){ perror("gestionopen.fdopen"); exit(EXIT_FAILURE); }

/* Echo */
char ligne[MAX_LIGNE];
  while(fgets(ligne,10,dialogue)!=NULL)
  { 
    PtCellClient ptr = list;
    while (ptr != NULL) {
        envoieChat(ptr->client.socket,ligne);
        ptr = ptr->next;
    }
  }
  /* Termine la connexion */
  fclose(dialogue);
}

int gestion_chat_leger(int dialogue){
  gestionChat(&dialogue);
  return 0;
}

void lance_boucleseverChat(void *argument){

  int s=*(int *)argument;
  boucleServeur(s,gestion_chat_leger);

}

/* Fonction principale */
int main(){

char *service=PORT_DIFFUSION_UDP;

#ifdef DEBUG
fprintf(stdout,"Port TCP: %s\n",service);
#endif

// initialisation balise UDP

int balise;
balise=initialisationSocketUDP(service);
SocketPort Socket_Port;
Socket_Port.balise = balise;
Socket_Port.port=strtol(service,NULL,10) ;
gestionClientUDP(Socket_Port);

// Initialisation du serveur

int s;
s=initialisationServeur(service,MAX_CONNEXIONS);

// Traitement des connexions et des messages

//Lance de la boucle du chat 

int chat;
chat=initialisationServeur(PORT_CHAT_TCP,MAX_CONNEXIONS);
creat_task(lance_boucleseverChat,&chat,sizeof(int));

/* Lancement de la boucle d'ecoute */
boucleServeur(s,gestion_client_leger);

return 0;
}