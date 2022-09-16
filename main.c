#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "ops.h"


char **generateMap(int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int col = mapDimensions[MAP_COL];
    char **map = malloc(row * sizeof(char *));
    int i = 0;

    for (i = 0; i < row; i++)
        map[i] = malloc(col * sizeof(char));

    return map;
}

void wipeMap(char **map, int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int i;
    for (i = 0; i < row; i++)
    {
        free(map[i]);
        map[i] = NULL;
    }

    free(map);
    map = NULL;
}

void layMap(char **map, int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int col = mapDimensions[MAP_COL];

    int i;
    for (i = 0; i < row; i++)
    {
        if (i == 0 || i == row - 1)
        {
            memset(map[i], MARKER_BORDER, col);
        }
        else
        {
            memset(map[i], MARKER_BORDER, 1);
            memset(map[i] + 1, ' ', col - 2);
            memset(map[i] + col - 1, MARKER_BORDER, 1);
        }
    }
}

void insertEntity(char** map, int playerPosition[], int goalPosition[])
{
    int playerRow = playerPosition[MAP_ROW];
    int playerCol = playerPosition[MAP_COL];
    int goalRow = goalPosition[MAP_ROW];
    int goalCol = goalPosition[MAP_COL];

    map[playerRow][playerCol] = MARKER_PLAYER;
    map[goalRow][goalCol] = MARKER_GOAL;
}

static void printMap(char** map, int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int col = mapDimensions[MAP_COL];

    int i,j;
    for (i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");

    }
}

/* =============================================================================
=============================================================================
=============================================================================
=============================================================================*/

int main(int argc, char *argv[])
{
    int mapR, mapC, playerR, playerC, goalR, goalC;
    char input;
    int mapDimensions[] = {10, 10};
    int playerPosition[] = {2, 2};
    int goalPosition[] = {6, 6};
    char **map = generateMap(mapDimensions);

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
    
    layMap(map, mapDimensions);
    insertEntity(map, playerPosition, goalPosition);
    printMap(map, mapDimensions);
    wipeMap(map, mapDimensions);
    readUserInput(&input);

    while (input != UP && input != DOWN && input != LEFT && input != RIGHT)
    {
        printf("Wrong input - Only W,A,S,D allowed!\n");
        printf("\n");
        readUserInput(&input);
    }

    return 0;
}


/* test code 
int main(int argc, char *argv[])
{
    int mapDimensions[] = {10, 10};
    int playerPosition[] = {1, 1};
    int goalPosition[] = {8, 8};

    char **map = generateMap(mapDimensions);
    layMap(map, mapDimensions);
    insertEntity(map, playerPosition, goalPosition);
    printMap(map, mapDimensions);
    wipeMap(map, mapDimensions);

    return 0;
}

*/