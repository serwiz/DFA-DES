#include <stdlib.h>
#include <stdio.h>

#include "../header/include.h"

/**
 * @author SERHAN Wissam
 * @date Mars 2021
 * 
 **/

int main(int argc, char** argv) {

    if (argc != 4) {
        printf("Error: Invalid input args.");
        return 1;
    }
    
    couleur(BLEU);
    couleur("1");
    printf("\n\n        ________________DFA_ON_DES________________\n\n\n");
    couleur(O);
    long clear_message;
    long encrypted_message;
    long *encrypted_wrong = malloc(32 * sizeof(long));

    if (init_var(argv, &clear_message, &encrypted_message, encrypted_wrong)) {
        printf("Error: Initialisation failed.");
        return 2;
    }
    printf("[");
    couleur(BLEU);
    printf("INFO");
    couleur(O);
    printf("]");
    printf("        Researching secret key K...\n\n");
    
    uint64_t K16 = generateK16(encrypted_message, encrypted_wrong);
    printf("[");
    couleur(BLEU);
    printf("INFO");
    couleur(O);
    printf("]");
    printf("        Key K16 found:\n");
    couleur("1");
    printf("                    %lx \n\n", K16);
    couleur(O);

    printf("[");
    couleur(BLEU);
    printf("INFO");
    couleur(O);
    printf("]");
    printf("        Reverse key schreduling on K16...");
    K16 = reverse_keyschred(K16);
    printf("  Done:\n");
    couleur("1");
    printf("                    %lx \n\n", K16);
    couleur(O);

    uint64_t K;
    printf("[");
    couleur(BLEU);
    printf("INFO");
    couleur(O);
    printf("]");
    printf("        Exhaustive attack on missing bits...");
    K = exhaustive_attack(clear_message, encrypted_message, K16);
    printf("  Done:\n");
    couleur("1");
    printf("                    %lx \n\n", K);
    couleur(O);

    printf("[");
    couleur(BLEU);
    printf("INFO");
    couleur(O);
    printf("]");
    printf("        Adding parity bits...");
    K = add_parity_bits(K);
    printf("  Done:\n");
    couleur("1");
    printf("                    %lx \n\n", K);
    couleur(O);

    printf("[");
    couleur(BLEU);
    printf("INFO");
    couleur(O);
    printf("]");
    printf("        Secret key found :\n\n");
    couleur(JAUNE);
    couleur("1");
    printf("                    %lx\n\n", K);
    couleur(O);

    printf("[");
    couleur(BLEU);
    printf("INFO");
    couleur(O);
    printf("]");
    printf("        Checking DES output with secret key:\n");
    if(DES(clear_message, K) == encrypted_message) {
        couleur(VERT);
        couleur("1");
        couleur("5");
        printf("\n        Successful attack on secret key.\n\n");
    }
    else {
        couleur(ROUGE);
        couleur("1");
        couleur("5");
        printf("        Fail attack on secret key.\n\n");
    }
    couleur(O);


    couleur(BLEU);
    couleur("1");
    printf("\n      ____________________END___________________\n\n\n");
    couleur(O);
    free(encrypted_wrong);
    return 0;
}