#include "graphics.h"
#include "constants.h"
#include <stdbool.h>
#include <stdlib.h>


// Placeholder values for global variables
int** arena = NULL;
int** exceptions = NULL;
int total_markers = 0;
int total_obstacles = 0;
int total_exceptions = 0;
int width = 0;
int height = 0;


// Generate random int between min and max (both inclusive)
int randInt(int min, int max) {
  return rand() % (max - min + 1) + min;
}


// Add coordinates to list of exceptions so that the coordinate isn't used for anything else
void addException(int* coord) {
  total_exceptions ++;
  if (total_exceptions == 1) {
    exceptions = malloc(total_exceptions * sizeof(int*));
  } else {
    exceptions = realloc(exceptions, total_exceptions * sizeof(int*));
  }
  exceptions[total_exceptions - 1] = malloc(2 * sizeof(int));
  exceptions[total_exceptions - 1][0] = coord[0];
  exceptions[total_exceptions - 1][1] = coord[1];
}


int** generateObstacles() {
  total_obstacles = randInt((width * height) / 4, (width * height) / 2.5);
  int** coords = malloc(total_obstacles * sizeof(int*));

  for (int i = 0; i < total_obstacles; i ++) {
    coords[i] = malloc(2 * sizeof(int));
    coords[i][0] = randInt(1, width - 2);
    coords[i][1] = randInt(1, height - 2);
    addException(coords[i]);
  }

  return coords;
}


// Returns true if coordinate is an empty square
bool emptySquare(int* coord) {
  for (int i = 0; i < total_exceptions; i ++) {
    if (coord[0] == exceptions[i][0] && coord[1] == exceptions[i][1]) return true;
  } return false;
}


int** generateMarkers() {
  total_markers = randInt(4, (width * height) / 20);
  int** coords = malloc(total_markers * sizeof(int*));

  for (int i = 0; i < total_markers; i ++) {
    coords[i] = malloc(2 * sizeof(int));
    do {
      coords[i][0] = randInt(1, width - 2);
      coords[i][1] = randInt(1, height - 2);
    } while (emptySquare(coords[i]));
    addException(coords[i]);
  }

  return coords;
}


// Returns true if object coordinates were at given (x, y) and inserts object
// Otherwise, it returns false
bool insertObject(int** coords, int len, int x, int y, int value) {
  for (int i = 0; i < len; i ++) {
    if (x == coords[i][0] && y == coords[i][1]) {
      arena[y][x] = value;
      return true;
    }
  } return false;
}


/*
Key:
0 = empty
1 = wall
2 = obstacle
3 = marker
*/


void createArena() {
  int** obstacle_coords = generateObstacles();
  int** marker_coords = generateMarkers();
  arena = malloc(height * sizeof(int*));
  bool flag;

  for (int y = 0; y < height; y ++) {
    arena[y] = calloc(width, sizeof(int));

    for (int x = 0; x < width; x ++) {
      if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
        // Insert walls
        arena[y][x] = 1;
      } else {
        flag = false;
        // Insert obstacle
        flag = insertObject(obstacle_coords, total_obstacles, x, y, 2);
        // Insert marker
        if (!flag) flag = insertObject(marker_coords, total_markers, x, y, 3);
      }
    }
  }

  // Free memory
  for (int i = 0; i < total_obstacles; i ++) {
    free(obstacle_coords[i]);
  } free(obstacle_coords);

  for (int i = 0; i < total_markers; i ++) {
    free(marker_coords[i]);
  } free(marker_coords);
}


void drawWhiteSquare(int x, int y) {
  setColour(white);
  fillRect(x * SIZE, y * SIZE, SIZE, SIZE);
}


void drawGreenSquare(int x, int y) {
  setRGBColour(0, 204, 0);
  fillRect(x * SIZE, y * SIZE, SIZE, SIZE);
}


void drawEmptySquare(int x, int y) {
  setColour(black);
  drawRect(x * SIZE, y * SIZE, SIZE, SIZE);
}


void drawWall(int x, int y) {
  setRGBColour(204, 51, 0);
  fillRect(x * SIZE, y * SIZE, SIZE, SIZE);
}


void drawObstacle(int x, int y) {
  setColour(black);
  fillRect(x * SIZE, y * SIZE, SIZE, SIZE);
}


void drawMarker(int x, int y) {
  setColour(gray);
  fillRect(x * SIZE, y * SIZE, SIZE, SIZE);
}


void drawArena() {
  background();
  for (int y = 0; y < height; y ++) {
    for (int x = 0; x < width; x ++) {
      switch (arena[y][x]) {
        case 0:
          drawEmptySquare(x, y);
          break;
        case 1:
          drawWall(x, y);
          break;
        case 2:
          drawObstacle(x, y);
          break;
        case 3:
          drawMarker(x, y);
      }
    }
  }
}
