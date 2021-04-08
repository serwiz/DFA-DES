#include <stdint.h>
#include "../header/data_des.h"

long permutation(uint64_t chiffre, int IP[], int size_in, int size_out) {
    long resultat = 0x0L;
    long bit;

    for (int i = 0; i < size_out; i++) {
        // On récupére le bit à la position size_in - IP[i], c-a-d 
        // la position correspondante à la permutation IP
        bit = 0x1L << (size_in - IP[i]);
        bit &= msg;
        //On remet le bit a 1 dans sa position avant permutation si il vaut 1
        if (tmp != 0) {
            tmp = 0x1L << (size_out - (i+1));
        }
        resultat |= tmp;
    }
    return resultat;
}

long P(uint64_t chiffre) {
    return permutation(chiffre, IP, 64, 64);
}

void init_R15_L16(uint64_t encrypted_message, uint32_t *R_15, uint32_t *L_16) {
    *L_16 = (encrypted_message >> 32) & 0xFFFFFFFFL;
    *R_15 = encrypted_message & 0xFFFFFFFFL;
}

uint32_t E(uint32_t R15) {
    return permutation(R15, E, 32, 48);
}