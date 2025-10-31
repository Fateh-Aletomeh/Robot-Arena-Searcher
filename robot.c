#ifndef GRAPHICS_H
#define GRAPHICS_H

enum colour {black,blue,cyan,darkgray,gray,green,lightgray,magenta,orange,pink,red,white,yellow};
typedef enum colour colour;

void drawLine(int, int, int, int);
void drawRect(int, int, int, int);
void fillRect(int, int, int, int);
void drawOval(int, int, int, int);
void fillOval(int, int, int, int);
void drawArc(int, int, int, int, int, int);
void fillArc(int, int, int, int, int, int);
void drawPolygon(int, int[], int[]);
void fillPolygon(int, int[], int[]);
void drawString(char*, int, int);
void displayImage(char*, int, int);

void setColour(colour);
void setRGBColour(int, int, int);

void foreground(void);
void background(void);
void clear(void);

void setWindowSize(int, int);

void sleep(int);

#endif


#include "constants.h"
#include "background.h"
#include <stdlib.h>


/*
Sources:
https://medium.com/@ojhasaurabh2099/traversing-a-grid-using-dfs-ac7a391f7af8
*/


char images[4][14] = {"Car_Up.png", "Car_Right.png", "Car_Down.png", "Car_Left.png"};


void drawRobot(Robot* obj, int delay) {
  foreground();
  clear();
  displayImage(images[obj->direction], obj->x * SIZE, obj->y * SIZE);
  sleep(delay);
}


// Generates coordinates of robot's home (start and end point)
int* createHome() {
  int* coord = malloc(2 * sizeof(int));
  do {
    coord[0] = randInt(1, width - 2);
    coord[1] = randInt(1, height - 2);
  } while (! emptySquare(coord));
  return coord;
}


void drawHome(int* coord) {
  background();
  displayImage("Home.png", coord[0] * SIZE, coord[1] * SIZE);
  foreground();
}


// Initialise robot's memory by setting all coords to 0
void initMemory(Robot* obj) {
  obj->memory = malloc(height * sizeof(int*));
  for (int y = 0; y < height; y ++) {
    obj->memory[y] = calloc(width, sizeof(int));
  }
}


void forward(Robot* obj) {
  switch (obj->direction) {
    case 0:
      obj->y --;
      break;
    case 1:
      obj->x ++;
      break;
    case 2:
      obj->y ++;
      break;
    case 3:
      obj->x --;
  }
}


void left(Robot* obj) {
  (obj->direction == 0) ? obj->direction = 3 : obj->direction --;
}


void right(Robot* obj) {
  (obj->direction == 3) ? obj->direction = 0 : obj->direction ++;
}


bool atMarker(Robot* obj) {
  return arena[obj->y][obj->x] == 3;
}


bool canMoveForward(Robot* obj) {
  switch (obj->direction) {
    case 0:
      return ! (arena[obj->y - 1][obj->x] == 1 | arena[obj->y - 1][obj->x] == 2);
    case 1:
      return ! (arena[obj->y][obj->x + 1] == 1 | arena[obj->y][obj->x + 1] == 2);
    case 2:
      return ! (arena[obj->y + 1][obj->x] == 1 | arena[obj->y + 1][obj->x] == 2);
    case 3:
      return ! (arena[obj->y][obj->x - 1] == 1 | arena[obj->y][obj->x - 1] == 2);
  }
}


void pickUpMarker(Robot* obj, bool show_path, bool draw) {
  obj->markers ++;
  if (draw) arena[obj->y][obj->x] = 0;
  background();
  if (show_path) {
    drawGreenSquare(obj->x, obj->y);
  } else {
    drawWhiteSquare(obj->x, obj->y);
    drawEmptySquare(obj->x, obj->y);
  }
}


void dropMarker(Robot* obj) {
  obj->markers --;
  arena[obj->y][obj->x] = 3;
  background();
  drawMarker(obj->x, obj->y);
  foreground();
}


int markerCount(Robot* obj) {
  return obj->markers;
}


// Leaves a green trace wherever the robot moves
void leaveTrace(int* home, int x, int y) {
  if (! (home[0] == x && home[1] == y)) {
    background();
    drawGreenSquare(x, y);
    foreground();
  }
}


// Returns true if cell has been visited already
bool visited(Robot* obj) {
  return obj->memory[obj->y][obj->x] == 1;
}


void goBack(Robot* obj) {
  left(obj);
  left(obj);
  forward(obj);
  left(obj);
  left(obj);
}


void dfs(Robot* obj, int* home, bool draw, bool show_path, int delay) {
  // Mark cell as visited
  obj->memory[obj->y][obj->x] = 1;
  
  if (show_path) leaveTrace(home, obj->x, obj->y);
  if (atMarker(obj)) pickUpMarker(obj, show_path, draw);

  // Call dfs recursively
  for (int i = 0; i < 4; i ++) {
    forward(obj);
    bool visit = visited(obj);
    goBack(obj);
    
    if (!visit && canMoveForward(obj)) {
      forward(obj);
      if (draw) drawRobot(obj, delay);
      dfs(obj, home, draw, show_path, delay);
      goBack(obj);
      if (draw) drawRobot(obj, delay);
    }

    right(obj);
  }
}
