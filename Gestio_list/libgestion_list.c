#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgestion_list.h"

PtCellClient allocate_Client(Client client) {
    PtCellClient ptr = malloc(sizeof(CellClient));

    ptr->client = client;
    ptr->next   = NULL;

    return ptr;
}

void append_to_Client_list(ListClient * list, Client client) {
    PtCellClient ptr = allocate_Client(client);
    if (ptr == NULL) { return; }

    ptr->next = *list;
    *list     = ptr;
}

int compare_Client(Client reference, Client client) {
    if(reference.socket==client.socket) {
        return 1;
    }
    else   return 0;
}

PtCellClient search_Client(ListClient list, Client Client) {
    PtCellClient ptr = list;

    while (ptr != NULL) {
        if (compare_Client(ptr->client, Client) == 1) { return ptr; }
        ptr = ptr->next;
    }

    return NULL;
}

bool add_Client_to_list(ListClient * list, Client client) {
    if (search_Client(*list, client)==NULL) {
        append_to_Client_list(list, client);
        return true;
    }else 
    {
        return false;
    }
}

void delete_last_Client(ListClient * list) {
   
    PtCellClient ptr = *list;
    *list         = ptr->next;
    free(ptr);
}

bool delete_Client_to_list(ListClient * list,Client client) {
    
    ListClient *list2=list;
    PtCellClient ptr = search_Client(*list2, client);
    if(ptr!=NULL) {
        
        *list2         = ptr->next;
        free(ptr);
        return true;
    }else return false;  
     
}

void delete_Client_list(ListClient * list) {
    PtCellClient ptr = *list;

    while (ptr != NULL) {
        delete_last_Client(&ptr);
    }
}

void display_Client(Client client) {
    printf("----------------------------------------\n");
    printf("pseudo:\t\t\t%s\n", client.pseudo);
    printf("id:\t%s\n", client.id);
    printf("socket:\t%d\n", client.socket);
}


void display_Client_list(ListClient list) {
    PtCellClient ptr = list;

    while (ptr != NULL) {
        display_Client(ptr->client);
        ptr = ptr->next;
    }
}
