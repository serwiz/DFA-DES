#include <stdlib.h>
#include <stdio.h>


#include "../header/init.h"

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
    
    printf("\n________________DFA_ON_DES________________\n");
    
    long clear_message;
    long encrypted_message;
    long *encrypted_wrong = malloc(32 * sizeof(long));

    if (init_var(argv, &clear_message, &encrypted_message, encrypted_wrong)) {
        printf("Error: Initialisation failed.");
        return 2;
    }

    
    /*for (int i=0; i<32; i++) {
        printf("%d: %lx \n", i, encrypted_wrong[i]);
    }*/

    printf("\n____________________END___________________\n");

    free(encrypted_wrong);
    return 0;
}