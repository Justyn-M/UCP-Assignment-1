#ifndef MACROS_H
#define MACROS_H

#define FALSE 0
#define TRUE !FALSE

#define BETWEEN(min, max, value) ((value <= max && value >= min) ? TRUE : FALSE)

/* Map Dimension Indexs */
#define MAP_ROW 0
#define MAP_COL 1

/* Entity Indexes */
#define ENT_ROW 0
#define ENT_COL 1
#define ENT_DIR 2

/* Entity Size */
#define ENT_SIZE 3

/* Entity Markers */
#define MARKER_BORDER '*'
#define MARKER_PLAYER 'P'
#define MARKER_GOAL 'G'
#define MARKER_FLOOR 'X'

/* Entity Directions */
#define DIR_UP 'u'
#define DIR_DOWN 'r'
#define DIR_LEFT 'l'
#define DIR_RIGHT 'r'

/* Player Controls */
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

/* Refresh Map Indexs */
#define REF_MAP 0
#define REF_MAP_DIM 1
#define REF_PLAYER 2
#define REF_GOAL 3

/* Game States */
#define GAME_STILL_PLAYING 0
#define GAME_WON 1
#define GAME_LOST 2

#endif