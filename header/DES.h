#ifndef H_DES_H
#define H_DES_H

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
long P(uint64_t chiffre);

/**
 * Wrapper de la fonction permutation pour E , 32, 48
 * ce qui correspond à la fonction d'expansion
 * @param chiffre   le chiffre juste
 * @return permutation(chiffre, E, 64, 64)
 **/
uint32_t E(uint32_t R15);

/**
 * Initialise les valeurs R15 et L16 pour le chiffre donnée (vrai ou faux)
 * 
 **/
    void init_R15_L16(uint64_t encrypted_message, uint32_t *R_15, uint32_t *L_16);

#endif