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

#define MAX_LIGNE     50
#define MAX_SERVICE   64
#define OLDER 1
#define EARLIER (-1)
#define EQUAL 0
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

/* Echo */
char ligne[MAX_LIGNE];
while(fgets(ligne,MAX_LIGNE,dialogue)!=NULL){ 
    //fprintf(dialogue,"> %s\n",ligne);

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
                sprintf(input, "idclient %d", id_client);
                fputs(input,dialogue);
              }else fprintf(dialogue,"> Vous etes déjà inscrit\n");

            }else if (strcmp(ligne1,CMD_ENDGAME)==0){

              strcpy(client.pseudo,ligne2);
              if(delete_Client_to_list(&list,client)==true){
                char message[80];
                sprintf(message, "Le pseudo %s a ete supprime ", client.pseudo);
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

printf("%d\n",balise);

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