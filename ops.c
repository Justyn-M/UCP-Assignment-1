#include <stdio.h>
#include <stdlib.h>

#include "macros.h"
#include "ops.h"

void readUserInput(char *Input)
{
    /* MENU: */
    printf("%c to go/face up\n", UP);
    printf("%c to go/face down\n", DOWN);
    printf("%c to go/face left\n", LEFT);
    printf("%c to go/face right\n", RIGHT);
    printf("action: ");
    scanf(" %c", Input);
    printf("\n");
}