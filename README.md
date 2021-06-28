# XMAZE
Jeu Graphique en réseau

Auteurs : ARADUKUNDA God-Belange - LEMAIRE Quentin

*********************************************************************************************************************************
                                            Liste des fonctionnalités côté serveur
*********************************************************************************************************************************

Serveur TCP multithreadé qui peut gérer plusieurs clients en simultanée.
Le serveur s'annonce (broadcast UDP) et gère correctement l'inscription des clients.
Il sert également de relais pour retransmettre les messages des joueurs aux autres joueurs (tchat).
Le serveur récupère les commandes des touches que le client lui envoie

*********************************************************************************************************************************
                                            Liste des fonctionnalités côté client
*********************************************************************************************************************************

Le client écoute le réseau afin d'attendre qu'un serveur est disponible (broadcast UDP).
Dés lors qu'un serveur est disponible, il peut faire sa connexion à ce dernier.
Pour s'inscrire, nous lui demandons d'envoyer dans un premier temps son pseudo afin que le serveur l'ajoute dans la liste
Le client gère le tchat : il peut écrire un message qui sera envoyé en UDP au serveur et recevoir également un message arrivant
du serveur.
Nous avons également la possibilité de se désincrire du serveur en envoyant le signal SIGINT (Ctrl + x)
La gestion d'envoie des touches se fait à l'aide de la librairie libgraph qui gère la détection d'évènement lié aux touches.

*********************************************************************************************************************************
                                            Lancement du programme
*********************************************************************************************************************************

Dans chaque partie se trouve un makefile qui s'occupe de la compilation. 
Ces makefiles peuvent être lancé à l'aide du Makefile général.

Pour tester le programme :
 - Taper "make" dans le dossier racine pour pouvoir compiler chaque partie
 - Se rendre dans le dossier ServeurJeu et lancer l'executable ./serveur pour lancer le serveur
 - Se rendre dans le dossier ClientJeu et lancer l'executable ./client pour lancer le client