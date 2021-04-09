#include <stdlib.h>
#include <stdio.h>

#include "../header/data_des.h"




int init_m(char * argv, long * m) {
    FILE * f = NULL;
    f = fopen (argv, "r");
    if (!f) {
        printf("Error: file %s can not be opened", argv);
        fclose(f);
        return 1;
    }
    fscanf(f, "%lx", m);
    fclose(f);
    return 0;
}

int init_c(char * argv, long * c) {
    FILE *f = NULL;
    f = fopen(argv, "r");
    if (!f)
    {
        printf("Error: file %s can not be opened", argv);
        fclose(f);
        return 1;
    }
    fscanf(f, "%lx", c);
    fclose(f);
    return 0;
}

int init_c_wrong(char * argv, long * c_wrong) {
    FILE *f = NULL;
    f = fopen(argv, "r");
    if (!f)
    {
        printf("Error: file %s can not be opened", argv);
        fclose(f);
        return 1;
    }

    for (int i=0; i < NB_WRONG_CIPHER; i++) {
        fscanf(f, "%lx", (c_wrong+i));
    }

    return 0;
}

int init_var(char **argv, long *m, long *c, long *c_wrong)
{
    return init_m(argv[1], m) || init_c(argv[2], c) || init_c_wrong(argv[3], c_wrong);
}