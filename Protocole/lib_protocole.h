#ifndef _LIBPROTOCOLE_H_
#define _LIBPROTOCOLE_H_

/*
    ****************************************
    *									   *
    * Fichier lib_protocole.h			   *
    * Commun à tous les projets SE2A4 2021 *
    *									   *
    ****************************************
*/

/*** Définition des constantes ***/

/* Définition des ports de communication */

#define PORT_CHAT_TCP "9999"
#define PORT_DIFFUSION_UDP "9998"
#define PORT_TOUCHES_UDP 9997
#define PORT_GRAPHIQUE_UDP "9996"

/* Définition des commandes TCP */

#define CMD_IDENTIFIANT "\\"
#define CMD_CONNECTION "pseudo"
#define CMD_ENDGAME "endgame"
#define CMD_CRASH "c_cho"
#define CMD_IDCLIENT "iencli"

/*** Définition des structures de communication UDP ***/

/* Paquet d'identité du serveur */

typedef struct UDP_Diffusion {
    unsigned short id_serveur;
    unsigned short port_tcp;
    unsigned short port_udp_touches;
} pr_udp_identite_t;

/* Paquet d'envoi des touches */

typedef struct UDP_Touches {
    unsigned char id_client;
    unsigned char touches;
} pr_udp_touches_t;

/* Structures graphiques */

typedef struct {
    int x, y;
} coords_t;

typedef struct {
    int type;
    union {
        coords_t p[4];
    } def;
} objet_2d_t;

/* Paquet d'envoi des objets graphiques */

typedef struct UDP_graph {
  //  uint32_t nb_objets;
    objet_2d_t* objets;
} pr_udp_graph_t;

#endif
