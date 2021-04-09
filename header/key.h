#ifndef H_KEY_H
#define H_KEY_H

#include <stdint.h>


/**
 * Récupére la clé K16 grâce au chiffré juste et aux chiffrés faux
 * @param encrypted_message   message chiffré juste
 * @param encrypted_wrong     messages chiffrés avec fautes
 * @return  la clé K16
 **/
uint64_t generateK16(uint64_t encrypted_message, long * encrypted_wrong);


/**
 * Permet de récupérer la bonne clé K16 parmit les solutions en comparant
 * à l'ancienne clé préalablement testé et stocké 
 * @param solution[8][6][64]    les solutions possibles pour l'execution du DES
 * @param nb_solution[8][6]     le nombre de solution possible
 * @param sbox                  la S-Box à tester
 * @param K16                   la clé K16 actuellement stockée
 * @return la clé K16 trouvée juste
 **/ 
uint64_t find_K16(int solution[8][6][64], int nb_solution[8][6], int sbox, uint64_t K_16);


/**
 * Fonction inversant le key schreduling de l'algorithme DES pour récupérer 48 bits 
 * de la clé secréte K aux bons emplacement, on place la clé a 64 bits pour simplifier
 * les opération futur avec les 8 bits de parités faux ainsi que les 8 bits manquant faux 
 * également
 * @param K16   la clé K16
 * @return 48 bits de la clé secréte K 
 **/
uint64_t reverse_keyschred(uint64_t K_16);


/**
 * Attaque exhaustive sur les bits manquant de la clé secréte K
 * @param K_16  clé K_16 aprés inversion du key shcreduling 
 * @return 56 bits de la clé secréte K
 **/
uint64_t exhaustive_attack(uint64_t message, uint64_t encrypted, uint64_t K_16);

/**
 * Rajoute les 8 bits de parité à la clé secréte K pour 
 * arriver au 64 bits finaux de la clé
 * @param K     clé secréte sans les bits de parité
 * @return la clé finale secréte K
 **/
uint64_t add_parity_bits(uint64_t K);

#endif