#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "macros.h"
#include "ops.h"

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

    if(low <= high)
    {
        number = (rand() % (high-low+1)) + low;
    }

    return number;
}


/* ================ */


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

/* create a function using random that generates Xs on the map */
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
                if (randomNum < 10)
                {
                    map[i][j] = MARKER_FLOOR;
                }
            }
        }
    }
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

/* disable echo and canonical so that player can move without pressing enter */
static void disableEchoAndCanonical()
{
    system("stty -echo");
    system("stty -icanon");
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

/* function that checks if player has reached the goal, if so, print out the message and exit the game */
void checkGoal(int playerPosition[], int goalPosition[])
{
    if (playerPosition[MAP_ROW] == goalPosition[MAP_ROW] && playerPosition[MAP_COL] == goalPosition[MAP_COL])
    {
        printf("You Win!\n");
        exit(0);
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

    initRandom();

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
    
    disableEchoAndCanonical();
    layMap(map, mapDimensions);
    insertEntity(map, playerPosition, goalPosition);
    printMap(map, mapDimensions);
    readUserInput(Input);


    /* move player, every time the player moves, an X is placed on the map using random function */
    while (*Input != '=')
    {
        switch (*Input)
        {
        case UP:
            playerPosition[MAP_ROW]--;
            crossBorder(playerPosition, mapDimensions);
            break;
        case DOWN:
            playerPosition[MAP_ROW]++;
            crossBorder(playerPosition, mapDimensions);
            break;
        case LEFT:
            playerPosition[MAP_COL]--;
            crossBorder(playerPosition, mapDimensions);
            break;
        case RIGHT:
            playerPosition[MAP_COL]++;
            crossBorder(playerPosition, mapDimensions);
            break;
        default:
            printf("Invalid input\n");
            break;
        }

        map = generateMap(mapDimensions);
        system("clear");
        disableEchoAndCanonical();
        layMap(map, mapDimensions);
        insertEntity(map, playerPosition, goalPosition);
        insertX(map, mapDimensions);
        printMap(map, mapDimensions);
        checkGoal(playerPosition, goalPosition);
        readUserInput(Input);
        wipeMap(map, mapDimensions);

    }


    return 0;
}