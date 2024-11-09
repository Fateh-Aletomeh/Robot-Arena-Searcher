#include <stdbool.h>


int randInt(int min, int max);
void addException(int* coord);
int** generateObstacles();
bool emptySquare(int* coord);
int** generateMarkers();
bool insertObject(int** coords, int len, int x, int y, int value);
void createArena();
void drawWhiteSquare(int x, int y);
void drawGreenSquare(int x, int y);
void drawEmptySquare(int x, int y);
void drawWall(int x, int y);
void drawObstacle(int x, int y);
void drawMarker(int x, int y);
void drawArena();
