#ifndef __LIB_PROTOCOLE_H__
#define __LIB_PROTOCOLE_H__

/****************************************
*										*
* Fichier lib_protocole.h				*
* Commun à tous les projets SE2A4 2021	*
*										*
****************************************/



/*** Définitions des contenus des balises UDP ***/

/* Paquet d'identité des serveurs */
typedef struct UDP_Connexion{
	unsigned short id_serveur;
	unsigned short port_tcp;
	unsigned short port_udp_touches;
} pr_udp_identite_t;

/* Paquet d'envoi des touches */
typedef struct UDP_touches{
	unsigned char id_client;
	unsigned char touches;
} pr_udp_touches_t;

/* Objet graphique */
/***** NON DEFINITIF *****/
typedef struct objet{
//	unsigned short type;
//	unsigned short pos_x;
//	unsigned short pos_z;
} pr_objet_t;

/* Paquet d'envoi des objets graphiques */
/***** NON DEFINITIF *****/
typedef struct UDP_graph{
//	unsigned short nb_objets;
//	struct objet objets[nb_objets];
} pr_udp_graph_t;




/*** Défninitons des commandes dans les paquets TCP ***/

/* Définition des commandes TCP */
#define CMD_IDENTIFIANT "\\"
#define CMD_CONNECTION "pseudo"
#define CMD_ENDGAME "endgame"
#define CMD_CRASH "c_cho"
#define CMD_IDCLIENT "iencli"

#endif
