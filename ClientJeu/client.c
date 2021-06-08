
/** Fichiers d'inclusion **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>

#include "libreseau.h"
#include "lib_protocole.h"

#define MAX_SERVICE 1024
#define SERVICE_ECOUTE "1500"

/** Quelques constantes **/

/** Variables globales */

/** Fonctions **/

void client_listenUDP(char *servecoute)
{
#ifdef DEBUG
fprintf(stdout,"j attends un serveur\n");
#endif

pr_udp_identite_t mess;
pr_udp_identite_t *messageptr = &mess;

int balise;
balise=initialisationSocketUDP(servecoute);

void *adresse=NULL;
while (1) 
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
if(s>0) // Si tout s'est passé lors de la connexion
    {
#ifdef DEBUG
  fprintf(stdout,"Connexion au serveur effectuée \n");
#endif 
    }
else{
#ifdef DEBUG
  fprintf(stderr,"Erreur de connexion au serveur\n"); exit(EXIT_FAILURE);
#endif 
  }
char tampon[100];
sprintf(tampon,"%s","pseudo bella");
write(s,tampon,100);   // s'inscrire 
shutdown(s,SHUT_RDWR);
}

/* Fonction principale */
int main(int argc,char *argv[]){
client_listenUDP(SERVICE_ECOUTE);
return 0;
}
