#ifndef OPS_H
#define OPS_H

void readInput(char *Input);
void crossBorder(int playerPosition[], int mapDimensions[]);
void checkGoal(int playerPosition[], int goalPosition[]);
void checkLoss(char **map, int playerPosition[]);

#endif