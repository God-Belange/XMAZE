#ifndef FLUX_EXECUTION_H
#define FLUX_EXECUTION_H
/**** Bibliotheque graphique (definitions) ****/

void creat_task(void (*f_prime)(void *),void *arg,int size);
void * f_prime(void * generic);

#endif /* FUNCTIONS_H */