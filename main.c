#include <stdio.h>
#include <stdlib.h>

#include "macros.h"

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

int main(int argc, char *argv[])
{
    int mapR, mapC, playerR, playerC, goalR, goalC;
    char input;
    if (argc != 7)
    {
        printf("./escape <row_map> <col_map> <row_player> <col_player> <row_goal> <col_goal>");
        return 1;
    }

    mapR = atoi(argv[1]);
    mapC = atoi(argv[2]);
    playerR = atoi(argv[3]);
    playerC = atoi(argv[4]);
    goalR = atoi(argv[5]);
    goalC = atoi(argv[6]);

    if (playerR == goalR && playerC == goalC)
    {
        printf("Invalid player/goal position\n");
        printf("Player cannot be on the goal");
        return 1;
    }
    else
        printf("Input: %d %d %d %d %d %d\n", mapR, mapC, playerR, playerC, goalR, goalC);

    /* if readuserinput is not w, a, s, d, then ask again and print 'wrong input */
    readUserInput(&input);
    while (input != UP && input != DOWN && input != LEFT && input != RIGHT)
    {
        printf("Wrong input - Only W,A,S,D allowed!\n");
        printf("\n");
        readUserInput(&input);
    }
    

    return 0;
}