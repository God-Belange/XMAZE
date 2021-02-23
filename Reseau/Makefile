#
# Makefile pour generer les executables du pont virtuel
#

OBJS_SWITCH=libreseau.o serveur.o
OBJS_CLIENT=libreseau.o client.o

CFLAGS += -Wall -DDEBUG

all: serveur client

#
# La cible de nettoyage
#

clean: 
	rm -f core *.o serveur client

#
# Les cibles
#

serveur:	$(OBJS_SWITCH)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SWITCH)
client:	$(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $@ $(OBJS_CLIENT)

libreseau.o: libreseau.c libreseau.h
serveur.o: serveur.c libreseau.h
client.o: client.c libreseau.h