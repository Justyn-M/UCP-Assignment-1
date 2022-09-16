#include <stdio.h>
#include <stdlib.h>

#include "macros.h"
#include "ops.h"

void readUserInput(char *Input)
{
    /* MENU: */
    printf("%c to go up\n", UP);
    printf("%c to go down\n", DOWN);
    printf("%c to go left\n", LEFT);
    printf("%c to go right\n", RIGHT);
    printf("action: ");
    scanf(" %c", Input);
    printf("\n");
}