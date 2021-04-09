#include <stdint.h>
#include "../header/data_des.h"

long permutation(uint64_t chiffre, int IP[], int size_in, int size_out) {
    long resultat = 0x0L;
    long bit;

    for (int i = 0; i < size_out; i++) {
        // On récupére le bit à la position size_in - IP[i], c-a-d 
        // la position correspondante à la permutation IP
        bit = 0x1L << (size_in - IP[i]);
        bit &= chiffre;
        //On remet le bit a 1 dans sa position avant permutation si il vaut 1
        if (bit != 0) {
            bit = 0x1L << (size_out - (i+1));
        }
        resultat |= bit;
    }
    return resultat;
}

uint64_t P_(uint64_t chiffre) {
    return permutation(chiffre, IP, 64, 64);
}

void init_R15_L16(uint64_t encrypted_message, uint32_t *R_15, uint32_t *L_16) {
    *L_16 = (encrypted_message >> 32) & 0xFFFFFFFFL;
    *R_15 = encrypted_message & 0xFFFFFFFFL;
}

uint64_t E_(uint32_t R15) {
    return permutation(R15, E, 32, 48);
}

uint64_t F_(uint64_t R, uint64_t Ki) {
    long S_Box_in, S_Box_out = 0x0;
    long row, column;
    long block;
    long ER;

    //printf("R = %lx,    Ki = %lx\n\n", R, Ki);
    ER = permutation(R, E, 32, 48);
    S_Box_in = ER ^ Ki;

    //printf ("SBOXIN : %lx\n", S_Box_in);

    for (int i=0; i<8; i++) {
        block= S_Box_in >> ((42 - (i *6)) & 0x3F);
        row = (2 * ((block & 0x20) >> 5)) + (block & 0x1);
        column = (block & 0x1E) >> 1;
        S_Box_out |= (S_Box[i][row][column] << (28 - (i *4)));
    }

    return permutation(S_Box_out, P, 32, 32);
}


long left_rotation(long K)
{
    uint64_t C28, D28;
    uint64_t test;

    C28 = (K & 0xFFFFFFF0000000) >> 28;
    D28 = K & 0xFFFFFFF;
    //On prend le bit le plus a droite
    test = C28 >> 27;
    //Décalage des bits à gauche
    C28 = C28 << 1;
    //On elnleve le bit de poids fort
    C28 = C28 & 0xFFFFFFF;
    C28 = C28 | test;
    //Choix du bit le plus à droite
    test = D28 >> 27;
    //Décalage des bits à gauche
    D28 = D28 << 1;
    //Suppression du bit de poids fort
    D28 = D28 & 0xFFFFFFF;
    //Mis à la position voulue
    D28 = D28 | test;

    C28 = C28 << 28;

    //printf ("~~~~~~~~~~~~~~~~\n");
    //printf ("retour : %lx \n", ((C28 | D28) & 0xFFFFFFFFFFFFFF));
    //printf ("~~~~~~~~~~~~~~~~\n");
    return ((C28 | D28) & 0xFFFFFFFFFFFFFF);
}

void key_schreduling(uint64_t Ki[], uint64_t K) {
    long T = permutation(K, PC1, 64, 56);

    for (int i = 0; i < 16; i++)
    {
        if (v[i] == 1)
            T = left_rotation(T);
        else
            T = left_rotation(left_rotation(T));

        Ki[i] = permutation(T, PC2, 56, 48);
    }
}

uint64_t DES(uint64_t message, uint64_t key) {
    uint64_t Ki[16] = {0};
    key_schreduling(Ki, key);
    /*printf("KEEEEEEYY\n");
    for(int i=0; i<16; i++) {
        printf("K%d = %lx\n", i, Ki[i]);
    }*/


    uint64_t IP_message = permutation(message, IP, 64, 64);

    uint32_t L = (IP_message & 0xFFFFFFFF00000000L) >> 32;
    uint64_t R = IP_message & 0x00000000FFFFFFFFL;

    uint32_t Li, Ri;
   // printf("##############\n\n");
    for(int i=0; i<16; i++) {
        //printf("tour %d: R = %lx\n", i, R);
        //printf("tour %d: L = %lx\n", i, L);

        Li = R;
        Ri = L ^ F_(R, Ki[i]);
        L = Li;
        R = Ri;
    }
    //printf("##############\n\n");
    
    return permutation((R << 32) | L, IP_Inv, 64, 64);
}