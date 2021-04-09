#ifndef H_DES_H
#define H_DES_H


#include <stdint.h>
/**
 * Permet la permutation de bit des chiffre en fonction de la matrice
 * de permutation IP donnée, de la taille en entrée voulue et de la taille 
 * en sortie voulue
 * @param chiffre   le chiffre juste
 * @param IP[]      la matrice des permutations
 * @param size_in  la taille de l'entrée donnée
 * @param size_out la taille de sortie voulue
 * @return le chiffre en entrée permuté
 **/
long permutation(uint64_t chiffre, int IP[], int size_in, int size_out);

/**
 * Wrapper de la fonction permutation pour IP[] , 64, 64
 * @param chiffre   le chiffre juste
 * @return permutation(chiffre, IP[], 64, 64)
 **/ 
uint64_t P_(uint64_t chiffre);

/**
 * Wrapper de la fonction permutation pour E , 32, 48
 * ce qui correspond à la fonction d'expansion
 * @param chiffre   le chiffre juste
 * @return permutation(chiffre, E, 64, 64)
 **/
uint64_t E_(uint32_t R15);

/**
 * Initialise les valeurs R15 et L16 pour le chiffre donnée (vrai ou faux)
 * @param encrypted_message message crypté servant de base
 * @param R_15              R15 à initialiser
 * @param L_16              L16 à initialiser
 * @return void
 **/
void init_R15_L16(uint64_t encrypted_message, uint32_t *R_15, uint32_t *L_16);

    
/**  
 * Effectue les rotation gauche pour le key schreduling de K
 * @param K     clé secréte K
 * @return le paramètre avec les rotations gauche du key shcreduling effectuée
 **/   
long left_rotation(long K);

/**
 * Initialise les Ki sous clé de K pour le chiffrement DES
 * @param Ki    tableau de stockage des différentes sous clés
 * @param K     clé secréte du chiffrement DES
 * @return void 
 **/
void key_schreduling(uint64_t Ki[], uint64_t K);



/**
 * Correspond à la fonction F des tours du schéme de feistel
 * du chiffrement DES
 * @param R     le Ri sur lequel sera effectué les opérations 
 * @param Ki    la sous clé Ki qui sera XOR avec R pour respecter le chiffrement DES
 * @return F(E(R) XOR Ki)
 **/
uint64_t F_(uint64_t R, uint64_t Ki);


/**
 * Algorithme de chiffrement DES
 * @param message   message clair à chiffrer
 * @param key       clé secréte K
 * @return chiffrement DES du message par la clé K
 **/
    uint64_t DES(uint64_t message, uint64_t key);

#endif