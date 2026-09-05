#ifndef CONSTANTS_H
#define CONSTANTS_H

extern int **arena;
extern int **exceptions;
extern int total_markers;
extern int total_obstacles;
extern int total_exceptions;
extern int WIDTH;
extern int HEIGHT;
extern int SIZE;

typedef struct {
  int x, y;
  int direction;
  int markers;
  int **memory;
} Robot;

#endif
