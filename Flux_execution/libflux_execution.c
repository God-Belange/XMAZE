#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "libflux_execution.h"
#define MAX_LIGNE 50

struct argu{
  void (*f) (void *);
  void * arg;
};

// void * option(void *arg)
// {
// 	*(int *)arg /= 2;
// 	return NULL;
// }

void creat_task(void (*f)(void *),void *arg,int size){
    
    pthread_t tid;
    struct argu *sa= malloc(sizeof(struct argu));
    if(arg!=NULL) 
    {
      sa->arg = malloc(size);
      memcpy(sa->arg,arg,size);
    }
    else 
    {
      sa->arg=NULL;
    }
    
    sa->f=f;
    pthread_create(&tid,NULL,f_prime,sa);
    pthread_detach(tid);
}

void * f_prime(void * generic){
    struct argu *sa= generic;
    sa->f(sa->arg);
    if(sa->arg!=NULL)  free(sa->arg);
    free(sa);
    return NULL;
}