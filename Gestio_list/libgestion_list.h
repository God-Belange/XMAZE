#ifndef _LIBGESTIONLIST_H_
#define _LIBGESTIONLIST_H_
#define MAX_LIGNE     50

/** Gestion listes des clients 
   ____________________________**/

typedef struct Client Client;
struct Client {
   char pseudo[MAX_LIGNE];
   char id[MAX_LIGNE];
   int socket;

};

typedef struct CellClient CellClient;
struct CellClient {
    CellClient * next;
    Client   client;
};

typedef CellClient * ListClient;
typedef CellClient * PtCellClient;

PtCellClient allocate_client(Client client);

void append_to_client_list(ListClient * list, Client client);

void delete_last_client(ListClient * list);
void delete_client_list(ListClient * list);
int size_of_client_list(ListClient list);

PtCellClient search_client(ListClient list, Client client);

bool add_Client_to_list(ListClient * list, Client client);

void display_Client_list(ListClient list);

bool delete_Client_to_list(ListClient * list,Client client);


#endif