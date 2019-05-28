#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "function.h"
#include "shell.h"


int main(){
    // Deklaracja Handlera katalogow
    struct HandlerC *headC;
    headC = malloc(sizeof(struct HandlerC));
    headC->beg = NULL;
    headC->end = NULL;
    // Deklaracja Handlera plyt
    struct HandlerR *headR;
    headR = malloc(sizeof(struct HandlerR));
    headR->beg = NULL;
    headR->end = NULL;

    puts("BAZA PŁYT:");
    helpFunc();

    loop(headC, headR);

    // Zwolnienie pamieci
    free(headC);
    free(headR);

    return 0;
}
