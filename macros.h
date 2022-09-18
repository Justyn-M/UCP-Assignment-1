#ifndef MACROS_H
#define MACROS_H

#define FALSE 0
#define TRUE !FALSE

/* Map Dimension Indexs */
#define MAP_ROW 0
#define MAP_COL 1

/* Entity Markers */
#define MARKER_BORDER '*'
#define MARKER_PLAYER 'P'
#define MARKER_GOAL 'G'
#define MARKER_FLOOR 'X'

/* Player Controls */
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

/* Game States */
#define GAME_STILL_PLAYING 0
#define GAME_WON 1
#define GAME_LOST 2

#endif