# Projet de Calcul Sécurisé : Attaque par faute sur le DES

## Introduction
----------

Projet de Calcul Sécurisé sur une ["Differential Fault Analysis" (DFA)]("https://fr.wikipedia.org/wiki/Attaque_par_faute") de l'algorithme de chiffrement DES encadré par **Mr. Goubin**. Nous disposons du message initial en clair, de son chiffré juste ainsi que de 32 chiffrés fautés sur différents bits. Il conviendra d'exploiter ces fautes et leur position pour remonter jusqu'à la clé secréte K.
l'application prend en entrée 3 fichiers contenant dans l'ordre :
* le message en clair
* le chiffre juste
* les 32 chiffrés faux

## Utilisation
----------

Le fichier est automatiser par un Makefile, pour l'utiliser veuiller l'utiliser comme suis :

Pour compiler :

    $> make compile

Pour executer le fichier :
    
    $> make compile
    $> make run
ou
    
    $> make exec

Pour clean les fichiers bin :
    
    $> make clean

Pour clean le projet :
    
    $> make mrproper
    
Il est également possible de lancer le projet avec gdb pour le debugging :

    $> make debug

⚠️ **Veillez à ne pas modifier les fichiers de configuration sous peine de pas voir fonctionner le projet**


## Configuration
----------

Le fichier étant entiérement configurable il est possible d'importer ses propres message.txt chiffre.txt ou chiffres_faux.txt.  
Il faut cependant faire attention à leur format :
* Pour message.txt et chiffre.txt écrire les données en hexadecimal de la sorte "4A7FBF8C2F0EAD97" sans espace.
* Idem pour chiffres_faux.txt veillez cependant à écrire un chiffré par ligne. 32 chiffrés sont nécessaire le cas écheant modifier la variable **NB_CYPHER_WRONG**

Il est possible de revenir à la version stable du projet grâce au git tag "V1.1"



### Copyright 
auteur: SERHAN Wissam  
date: Mars - Avril 2021    
    

