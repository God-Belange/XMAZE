#
# Makefile pour l'application de construction de labyrinthe
#

SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
BIBLIOTHEQUES = -L ../Reseau -lreseau -L ../Flux_execution -lflux_execution -lpthread
CFLAGS += -Wall -DDEBUG -I ../Reseau -I ../Flux_execution
CIBLE = serveur

#
# Nom de la cible principale
#

all: $(CIBLE)

#
# Cible de nettoyage
#

clean: 
	rm -f core *.o $(CIBLE)

#
# Dependances pour l'executable
#

$(CIBLE): $(OBJETS)
	$(CC) -o $@ $^ $(BIBLIOTHEQUES)