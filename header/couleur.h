#ifndef H_COULEUR_H
#define H_COULEUR_H


#define couleur(param) printf("\033[%sm", param)


#define BLEU "34"
#define ROUGE "31"
#define VERT "32"
#define O "0"
#define JAUNE "33"
#define CYAN "36"
#define MAGENTA "35"
#define BLANC "37"

/**
 * Affiche le status [INFO] dans le terminal
 **/
void info();

#endif