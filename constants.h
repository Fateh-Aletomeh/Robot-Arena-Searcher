#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SIZE 40


extern int** arena;
extern int** exceptions;
extern int total_markers;
extern int total_obstacles;
extern int total_exceptions;
extern int width;
extern int height;

struct Robot {
  int x, y;
  int direction;
  int markers;
  int** memory;
};

#endif
