# XMAZE
Jeu Graphique en réseau

Auteurs : ARADUKUNDA God-Belange - LEMAIRE Quentin

*********************************************************************************************************************************
                                            Liste des fonctionnalités côté serveur
*********************************************************************************************************************************

Serveur TCP multithreadé qui peut gérer plusieurs clients en simultanée.  
Le serveur s'annonce (broadcast UDP) et gère correctement les inscription et désincriptions des clients (utilisation d'une liste chainée)  
Il sert également de relais pour retransmettre les messages des joueurs aux autres joueurs (tchat).  


*********************************************************************************************************************************
                                            Liste des fonctionnalités côté client
*********************************************************************************************************************************

Le client écoute le réseau afin d'attendre qu'un serveur soit disponible (broadcast UDP).  
Dés lors qu'un serveur est disponible, il fait la connexion à ce dernier.    
Pour s'inscrire, nous lui demandons d'envoyer dans un premier temps son pseudo afin que le serveur l'ajoute dans la liste  
Le client peut utiliser le tchat en envoyant un message au serveur par la connexion TCP, le client reçoit également les message arrivant
du serveur(venant des aures clients).  
Nous avons également la possibilité de se désincrire du serveur en envoyant le signal SIGINT (Ctrl + c) ou en quittant la fênetre du jeu  
La gestion d'envoie des touches se fait à l'aide de la librairie libgraph qui gère la détection d'évènement lié aux touches. cette foctionnalité n'est pas totalement integrée.  

*********************************************************************************************************************************
                                            Lancement du programme
*********************************************************************************************************************************

Dans chaque partie se trouve un makefile qui s'occupe de la compilation.   
Ces makefiles peuvent être lancé à l'aide du Makefile général.  

Pour tester le programme :
 - Taper "make all" dans le dossier racine pour pouvoir compiler tous
 - Se rendre dans le dossier ServeurJeu et lancer l'executable ./serveur pour lancer le serveur
 - Se rendre dans le dossier ClientJeu et lancer l'executable ./client pour lancer le client
 - Côté client taper un pseudo, une fois inscrit, tester le tchat en envoyant un message
 - Pour tester, le tchat, on peut inscrire un autre clien via nc localhost ,ensuite taper " pseudo nompseudo", on reçoit le message envoyé via ./client


*********************************************************************************************************************************
                                           Travail restant
*********************************************************************************************************************************

L'intégration de la fonction demmarage_jeu(déjà développé) côté client  
Récuperation des touches via la connexion UDP côté serveur, et affichage des positions des  clients  
Calcul de la scène 3D et 2D  
Gestion des messages de contrôle


*********************************************************************************************************************************
                                          Conclusion
*********************************************************************************************************************************


Ce projet nous a permis, de comprendre :
 - Les connexions UDP et TCP, 
 - Comment on peut créer plusieures tâches multhraidées, et interagir entre elles, sans perturber le bon fonctionnement,
 - Nous avons appris comment marche la bibliothèque SDL, pour la création des jeux vidéo,
 - Nous avons également vu, comment oragniser un projet avec un arborsence contenant des bibliothèques,makefile,...






