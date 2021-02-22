#
# Makefile pour generer les executables du pont virtuel
#

OBJS_SWITCH=libreseau.o virtual_bridge.o
OBJS_CLIENT=libreseau.o virtual_client.o

CFLAGS += -Wall -DDEBUG

all: virtual_bridge virtual_client

#
# La cible de nettoyage
#

clean: 
	rm -f core *.o virtual_bridge virtual_client

#
# Les cibles
#

virtual_bridge:	$(OBJS_SWITCH)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SWITCH)
virtual_client:	$(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $@ $(OBJS_CLIENT)

libreseau.o: libreseau.c libreseau.h
virtual_bridge.o: virtual_bridge.c libreseau.h
virtual_client.o: virtual_client.c libreseau.h