#include <stdint.h>
#include "../header/data_des.h"
#include "../header/DES.h"

uint64_t generateK16(uint64_t encrypted_message, long * encrypted_wrong) {
    
    // Init L16 et R15
    encrypted_message = P(encrypted_message);
    uint32_t L_16, R_15;
    init_R15_L16(encrypted_message, &R_15, &L_16);

    
    uint64_t encrypted_wrong_tmp;
    uint32_t L_16_wrong, R_15_wrong;

    for(int sbox=0; sbox < nb_sbox; sbox++) {

        for(fault=0; fault < 6; fault++) {
            // Init pour le chiffré faux
            encrypted_wrong_tmp = P(encrypted_wrong[faulted_bits[sbox][fault]]);
            init_R15_L16(encrypted_wrong_tmp, &R_15_wrong, &L_16_wrong);


            // On établi le contexte des équations
            R_15 = E(R_15);
            R_15_wrong = E(R_15_wrong);

            
            // On résout les 8 équations du system permettant
            // de retrouver les portions de clés K16 possibles


        
        }
    }
}