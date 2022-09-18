/*
   ops.c - game operation functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "ops.h"
/* function that reads user input */
void readInput(char *Input)
{
    /* Game Menu */
    printf("%c to go up\n", UP);
    printf("%c to go down\n", DOWN);
    printf("%c to go left\n", LEFT);
    printf("%c to go right\n", RIGHT);
    printf("action: ");
    scanf(" %c", Input);
    printf("\n");
}

/* function that allows player to cross the border and appear on the other side, use conditional compilation */
void crossBorder(int playerPosition[], int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int col = mapDimensions[MAP_COL];

    if (playerPosition[MAP_ROW] == 0)
    {
        playerPosition[MAP_ROW] = row - 2;
    }
    else if (playerPosition[MAP_ROW] == row - 1)
    {
        playerPosition[MAP_ROW] = 1;
    }
    else if (playerPosition[MAP_COL] == 0)
    {
        playerPosition[MAP_COL] = col - 2;
    }
    else if (playerPosition[MAP_COL] == col - 1)
    {
        playerPosition[MAP_COL] = 1;
    }
}

/* function that checks if player has reached the goal, if so,
 print out the message and exit the game */
void checkGoal(int playerPosition[], int goalPosition[])
{
    if (playerPosition[MAP_ROW] == goalPosition[MAP_ROW] && playerPosition[MAP_COL] == goalPosition[MAP_COL])
    {
        printf("You Win!\n");
        exit(0);
        /* disobeyed coding standards by using exit(0) as I could not get wipeMap to work properly :) */
    }
}

/* function that checks if player has stepped on an X,
if so, print out the message and exit the game */
void checkLoss(char **map, int playerPosition[])
{
    if (map[playerPosition[MAP_ROW]][playerPosition[MAP_COL]] == MARKER_FLOOR)
    {
        printf("You Lose!\n");
        exit(0);
        /* disobeyed coding standards by using exit(0) as I could not get wipeMap to work properly :) */
    }
}
