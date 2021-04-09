#include <stdint.h>
#include <stdio.h>

#include "../header/data_des.h"
#include "../header/DES.h"

uint64_t find_K16(int solution[8][6][64], int nb_solution[8][6], int sbox, uint64_t K_16)
{
    

    long key_prob = (long)solution[sbox][0][0];
    int n_sol_wrong_a = 0;
    int n_sol_wrong_b;

    for (int fault = 1; fault < 6; fault++)
    {
        
        for (n_sol_wrong_b=0; n_sol_wrong_b < nb_solution[sbox][fault]; n_sol_wrong_b++) {
            if (key_prob == solution[sbox][fault][n_sol_wrong_b])
                break;
        }
        
        if (n_sol_wrong_b == nb_solution[sbox][fault])
        {

            if (n_sol_wrong_a + 1 >= nb_solution[sbox][0])
            {
                printf("Error: S-Box n°%d, can not find K16\n", sbox);
                return K_16;
            }
            
            fault = 1;
            ++n_sol_wrong_a;
            key_prob = (long)solution[sbox][0][n_sol_wrong_a];
        }
    }

    //printf("\nSolution S%d est : %lx \t \t |\t ", sbox + 1, key_prob);
    K_16 = (K_16 << 6) | key_prob;
    //printf("Update K16: %lx\n", K_16);

    return K_16;
}

uint64_t generateK16(uint64_t encrypted_message, long * encrypted_wrong) {

    uint64_t K_16;
    //2^6 solutions possibles des 6 fautes pour les 8 S-Box
    int solution[8][6][64] = {{{0}}};
    //Nombre de solutions possibles pour 6 chiffrés faux sur les 8 S-Box
    int nb_solution[8][6] = {{0}};

    // Init L16 et R15
    encrypted_message = P_(encrypted_message);
    uint32_t L_16, R_15;
    uint64_t ER_15, ER_15_wrong;
    init_R15_L16(encrypted_message, &R_15, &L_16);

    
    uint64_t encrypted_wrong_tmp;
    uint32_t L_16_wrong, R_15_wrong;
    uint32_t L_16_diff;

    uint32_t tmp, tmp_wrong;
    int row, column, r_wrong, c_wrong;
    int RES, SBOX;

    for(int sbox=0; sbox < nb_sbox; sbox++) {

        for(int fault=0; fault < 6; fault++) {
            // Init pour le chiffré faux
            encrypted_wrong_tmp = P_(encrypted_wrong[faulted_bits[sbox][fault]]);
            init_R15_L16(encrypted_wrong_tmp, &R_15_wrong, &L_16_wrong);


            // On établi le contexte des équations
            ER_15 = E_(R_15);
            ER_15_wrong = E_(R_15_wrong);


            L_16_diff = permutation(L_16^L_16_wrong, P_Inv, 32, 32);

            for(int Ki=0; Ki < 64; Ki++) {
                // Valeur d'entrée des S-Box
                tmp = ((ER_15 & get_6bits[sbox]) >> ((7- sbox) * 6)) ^ Ki;
                tmp_wrong = ((ER_15_wrong & get_6bits[sbox]) >> ((7 - sbox) * 6)) ^ Ki;

                // On passe dans les S-Box en récupérant la bonne ligne avec la bonne colonne
                row = 2 * ((tmp & 0x20) >> 5) + (tmp & 0x1);
                column = (tmp & 0x1E) >> 1;
                // pour chaque chiffre
                r_wrong = 2 * ((tmp_wrong & 0x20) >> 5) + (tmp_wrong & 0x1);
                c_wrong = (tmp_wrong & 0x1E) >> 1;

                // On stock les résultats finals
                RES = (L_16_diff & get_4bits[sbox]) >> ((7 - sbox) * 4);
                SBOX = S_Box[sbox][row][column] ^ S_Box[sbox][r_wrong][c_wrong];
                // Si les 4 bits de sortie sont identiques au bits de vérification 
                // alors Ki s'ajoute aux solutions
                if( RES == SBOX) {
                    solution[sbox][fault][nb_solution[sbox][fault]] = Ki;
                    nb_solution[sbox][fault]++;
                }
            }        
        }

        // Séléctionne la bonne clé K16
        K_16 = find_K16(solution, nb_solution, sbox, K_16);
    }
    return K_16;
}


uint64_t reverse_keyschred(uint64_t K_16) {

    return permutation(permutation(K_16, PC2_Inv, 48, 56), PC1_Inv, 56, 64);
}

uint64_t exhaustive_attack(uint64_t message, uint64_t encrypted, uint64_t K_16) {
    long mask = 0x00L;
    long missing;
    uint64_t K_tmp = K_16;

    //printf("11111111111111 K_16 = %lx\n", K_16);
    while (mask < 256 && encrypted != DES(message, K_16) ) {

        missing = 0x0L;

        for (int i=0; i<8; i++) {
            missing |= ((mask >> i) & 1) << (64 - missing_bit_pos[i]);
        }
        K_16 = K_tmp | missing;
        mask = mask + 1;
    }
        //if (mask == 256)
            //printf("Error: missing bits was not found\n");
    //printf("2222222222222 K_16 = %lx\n", K_16);
    return K_16;
}

uint64_t add_parity_bits(uint64_t K) {
    long tmp, parity;
    uint64_t K_tmp = K;
    //printf("Input BP %lx\n", K);
    for (int i=0; i<8; i++) {

        parity=0;

        for(int j=0; j<8; j++) {

            if (j!=7) {
                tmp = 0x1L << (((7 - i) * 8) + (7 - j));
                tmp = K & tmp;
                parity = tmp ? parity ^ 1 : parity ^ 0;
            }
            else {
                tmp = !parity;
                K_tmp |= tmp << ((7 - i) * 8);
            }
        }
    }
    //printf("Output BP %lx", K_tmp);
    return K_tmp;
}