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
#include "robot.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char** argv) {
  srand(time(NULL));
  width = randInt(22, 36);
  height = randInt(12, 18);
  bool run = true;
  struct Robot robot;
  int* home;

  // Default values for delay and show_path
  int delay = 50;
  bool show_path = false;

  // Change delay and show_path to what user decides
  if (argc == 3) {
    delay = atoi(argv[1]);
    show_path = atoi(argv[2]);
  }

  // Run the code until an arena is created that is possible
  while (run) {
    total_exceptions = 0;
    createArena();
    home = createHome();
    robot.x = home[0];
    robot.y = home[1];
    robot.direction = randInt(0, 3);
    robot.markers = 0;

    // Free memory
    for (int i = 0; i < total_exceptions; i ++) {
      free(exceptions[i]);
    } free(exceptions);

    initMemory(&robot);
    dfs(&robot, false, show_path, delay);

    if (robot.markers == total_markers) {
      // Erase robot's memory
      for (int i = 0; i < height; i ++) {
        free(robot.memory[i]);
      } free(robot.memory);
      
      setWindowSize(width * SIZE, height * SIZE);
      drawArena();

      robot.x = home[0];
      robot.y = home[1];
      initMemory(&robot);
      drawRobot(&robot, delay);

      dfs(&robot, true, show_path, delay);
      dropMarker(&robot);
      run = false;
    }

    // Free memory
    for (int i = 0; i < height; i ++) {
      free(arena[i]);
      free(robot.memory[i]);
    }
    free(arena);
    free(robot.memory);
    free(home);
  }

  return 0;
}
