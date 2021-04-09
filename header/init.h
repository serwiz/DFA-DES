#ifndef H_INIT_H
#define H_INIT_H



/**
 * Initialise les différentes variables du projet
 * @param argv      contenant les noms des fichiers d'initialisation
 * @param m         message clair à initialiser
 * @param c         chiffre juste à initialiser
 * @param c_wrong   chiffrés faux à initialiser
 * @return 0 si pas d'erreur 1 sinon
 **/
int init_var(char **argv, long *m, long *c, long * c_wrong);

/**
 * Initialise le message clair
 * @param argv      nom du fichier contenant le message
 * @param m         variable de stockage du message
 * @return 0 si pas d'erreur 1 sinon
 **/
int init_m(char *argv, long *m);

/**
 * Initialise le message chiffre juste
 * @param argv      nom du fichier contenant le chiffre juste
 * @param c        variable de stockage du chiffre juste
 * @return 0 si pas d'erreur 1 sinon
 **/
int init_c(char *argv, long *c);

/**
 * Initialise les message chiffres fautés
 * @param argv      nom du fichier contenant les chiffrés fautés
 * @param c_wrong   variable de stockage des chiffrés fautés
 * @return 0 si pas d'erreur 1 sinon
 **/
int init_c_wrong(char *argv, long * c_wrong);

#endif