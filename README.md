# Projet de Calcul Sécurisé : Attaque par faute sur le DES

## Introduction
-----

Projet de Calcul Sécurisé sur une ["Differential Fault Analysis" (DFA)]("https://fr.wikipedia.org/wiki/Attaque_par_faute") de l'algorithme de chiffrement DES encadré par **Mr. Goubin**. Nous disposons du message initial en clair, de son chiffré juste ainsi que de 32 chiffrés fautés sur différents bits. Il conviendra d'exploiter ces fautes et leur position pour remonter jusqu'à la clé secréte K.
l'application prend en entrée 3 fichiers contenant dans l'ordre :
* le message en clair
* le chiffre juste
* les 32 chiffrés faux

## Utilisation
-----

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

