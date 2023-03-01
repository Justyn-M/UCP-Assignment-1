/*
   main.c - main file for running the game
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "macros.h"
#include "ops.h"

/* Due to the bug in my vscode, I cannot create new .c files as they appear with
command-line error: language mods specified are incompatible C/C++ (1027) and also
sometimes gives random untold errors in other files.
I have tried for hours to fix this to no avail.
Hence I have said which functions should be in a new file */

/* ================ */
/* FOLLOWING FILES SHOULD BE IN random.c */
/* ================ */

/* random.c functins */

/*call this function just ONCE at the beginning of your program before using the random number generator */
void initRandom()
{
    srand(time(NULL));
}

/* Will return random integer between *low* and *high* inclusive.
   If the low is larger than the high, it will return -1 instead.
   In theory, it still works with negative *low* and *high* (as long as low is not larger than high), but for this assignment you will most likely not need the negative number.
   Please ensure you call initRandom function once before starting using this function. */
int random(int low, int high)
{
    int number = -1;

    if (low <= high)
    {
        number = (rand() % (high - low + 1)) + low;
    }

    return number;
}

/* ================ */
/* END OF FILES SHOULD BE IN random.c */
/* ================ */

/* ================ */
/* FOLLOWING FILES SHOULD BE IN map.c and called to main by map.h */
/* ================ */

/* function that generates the map */
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
/* function that wipes the map and free the memory */
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
/* function that lays the map borders */
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
/* function that inserts the player and goal into the map */
void insertEntity(char **map, int playerPosition[], int goalPosition[])
{
    int playerRow = playerPosition[MAP_ROW];
    int playerCol = playerPosition[MAP_COL];
    int goalRow = goalPosition[MAP_ROW];
    int goalCol = goalPosition[MAP_COL];

    map[playerRow][playerCol] = MARKER_PLAYER;
    map[goalRow][goalCol] = MARKER_GOAL;
}

/* function using random function to generate Xs on the map */
void insertX(char **map, int mapDimensions[])
{
    int row = mapDimensions[MAP_ROW];
    int col = mapDimensions[MAP_COL];
    int i;
    for (i = 0; i < row; i++)
    {
        int j;
        for (j = 0; j < col; j++)
        {
            if (map[i][j] == ' ')
            {
                int randomNum = random(0, 100);
                if (randomNum < 5)
                {
                    map[i][j] = MARKER_FLOOR;
                }
            }
        }
    }
}
/* function that prints the map */
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

/* END OF FUNCTIONS THAT SHOULD BE IN FILE map.c AND CALLED TO MAIN USING
map.h */

/* ================ */
/* FOLLOWING FILES ARE CORRECTLY PLACED INTO main.c */
/* ================ */

/* disable echo and canonical so that player can move without pressing enter */
static void disableEchoAndCanonical()
{
    system("stty -echo");
    system("stty -icanon");
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
    char **map;

    initRandom();

    if (argc != 7)
    {
        printf("Input: %s <map row> <map col> <player row> <player col> <goal row> <goal col>\n", argv[0]);
        return 1;
    }
    mapDimensions[MAP_ROW] = atoi(argv[1]);
    mapDimensions[MAP_COL] = atoi(argv[2]);
    playerPosition[MAP_ROW] = atoi(argv[3]);
    playerPosition[MAP_COL] = atoi(argv[4]);
    goalPosition[MAP_ROW] = atoi(argv[5]);
    goalPosition[MAP_COL] = atoi(argv[6]);

    /* player position and goal positions cannot be the same */
    if (playerPosition[MAP_ROW] == goalPosition[MAP_ROW] && playerPosition[MAP_COL] == goalPosition[MAP_COL])
    {
        printf("Player and goal positions cannot be the same\n");
        return 1;
    }


    map = generateMap(mapDimensions);
    /* used system clear to clear screen */
    system("clear");

    disableEchoAndCanonical();
    layMap(map, mapDimensions);
    insertEntity(map, playerPosition, goalPosition);
    printMap(map, mapDimensions);
    readInput(Input);

    while (1)
    {
        if (strcmp(Input, "w") == 0)
        {
            playerPosition[MAP_ROW]--;
            crossBorder(playerPosition, mapDimensions);
            system("clear");
            layMap(map, mapDimensions);
            insertEntity(map, playerPosition, goalPosition);
            insertX(map, mapDimensions);
            printMap(map, mapDimensions);
            checkGoal(playerPosition, goalPosition);
            checkLoss(map, playerPosition);
            readInput(Input);
        }
        else if (strcmp(Input, "s") == 0)
        {
            playerPosition[MAP_ROW]++;
            crossBorder(playerPosition, mapDimensions);
            system("clear");
            layMap(map, mapDimensions);
            insertEntity(map, playerPosition, goalPosition);
            insertX(map, mapDimensions);
            printMap(map, mapDimensions);
            checkGoal(playerPosition, goalPosition);
            checkLoss(map, playerPosition);
            readInput(Input);
        }
        else if (strcmp(Input, "a") == 0)
        {
            playerPosition[MAP_COL]--;
            crossBorder(playerPosition, mapDimensions);
            system("clear");
            layMap(map, mapDimensions);
            insertEntity(map, playerPosition, goalPosition);
            insertX(map, mapDimensions);
            printMap(map, mapDimensions);
            checkGoal(playerPosition, goalPosition);
            checkLoss(map, playerPosition);
            readInput(Input);
        }
        else if (strcmp(Input, "d") == 0)
        {
            playerPosition[MAP_COL]++;
            crossBorder(playerPosition, mapDimensions);
            system("clear");
            layMap(map, mapDimensions);
            insertEntity(map, playerPosition, goalPosition);
            insertX(map, mapDimensions);
            printMap(map, mapDimensions);
            checkGoal(playerPosition, goalPosition);
            checkLoss(map, playerPosition);
            readInput(Input);
        }
        else if (strcmp(Input, "q") == 0)
        {
            printf("You Quit!\n");
            exit(0);
            /* disobeyed coding standards because I could not get wipemap to work in main */
        }
        else
        {
            printf("Invalid Input! Try again:\n");
            readInput(Input);
        }
    }

    /* clear memory leaks */
    free(Input);
    free(map);

    return 0;
}