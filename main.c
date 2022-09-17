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

void insertEntity(char **map, int playerPosition[], int goalPosition[])
{
    int playerRow = playerPosition[MAP_ROW];
    int playerCol = playerPosition[MAP_COL];
    int goalRow = goalPosition[MAP_ROW];
    int goalCol = goalPosition[MAP_COL];

    map[playerRow][playerCol] = MARKER_PLAYER;
    map[goalRow][goalCol] = MARKER_GOAL;
}

static void printMap(char **map, int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int col = mapDimensions[MAP_COL];

    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
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

/* main that allows command line arguments to be the mapDimensions, playerPosition and goalPosition */
int main(int argc, char *argv[])
{
    char *Input = malloc(sizeof(char));
    int mapDimensions[2];
    int playerPosition[2];
    int goalPosition[2];

    if (argc != 7)
    {
        printf("Input: %s <map row> <map col> <player row> <player col> <goal row> <goal col>\n", argv[0]);
        printf("Any out of bounds values will result in a segmentation fault\n");
        return 1;
    }

    mapDimensions[MAP_ROW] = atoi(argv[1]);
    mapDimensions[MAP_COL] = atoi(argv[2]);
    playerPosition[MAP_ROW] = atoi(argv[3]);
    playerPosition[MAP_COL] = atoi(argv[4]);
    goalPosition[MAP_ROW] = atoi(argv[5]);
    goalPosition[MAP_COL] = atoi(argv[6]);

    char **map = generateMap(mapDimensions);
    system("clear");
    layMap(map, mapDimensions);
    insertEntity(map, playerPosition, goalPosition);
    printMap(map, mapDimensions);
    wipeMap(map, mapDimensions);
    readUserInput(Input);

    /* move player */

    while (*Input != 'q')
    {
        if (*Input == UP)
        {
            playerPosition[MAP_ROW]--;
        }
        else if (*Input == DOWN)
        {
            playerPosition[MAP_ROW]++;
        }
        else if (*Input == LEFT)
        {
            playerPosition[MAP_COL]--;
        }
        else if (*Input == RIGHT)
        {
            playerPosition[MAP_COL]++;
        }
        else
        {
            printf("Invalid input\n");
        }
        map = generateMap(mapDimensions);
        system("clear");
        layMap(map, mapDimensions);
        insertEntity(map, playerPosition, goalPosition);
        printMap(map, mapDimensions);
        wipeMap(map, mapDimensions);
        readUserInput(Input);
    }

    return 0;
}
