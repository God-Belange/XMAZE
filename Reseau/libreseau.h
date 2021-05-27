/** fichier libreseau.h **/

/******************************************************************/
/** Ce fichier decrit les structures et les constantes utilisees **/
/** par les fonctions reseau.                                    **/
/******************************************************************/

/**** Constantes ****/

/** Nombre maximum de connexions tamponnees pour le serveur **/

#define MAX_CONNEXIONS	32
#include "lib_protocole.h"

char trouve;

/**** Fonctions ****/

int connexionServeur(char *hote,char *service);
int initialisationServeur(char *service,int connexions);
int read_fixed(int descripteur,unsigned char *array,int size);
int boucleServeur(int ecoute,int (*traitement)(int));
int initialisationSocketUDP(char *service);
void *recevoirUDP(int s,void *message,int taille);
void *creationAddresseUDP(char *hote,char *service);
void envoyerUDP(int s,void *adresse,void *message,int taille);