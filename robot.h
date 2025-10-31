#include <stdbool.h>


void drawRobot(Robot* obj, int delay);
int* createHome();
void drawHome(int* coord);
void initMemory(Robot* obj);
void forward(Robot* obj);
void left(Robot* obj);
void right(Robot* obj);
bool atMarker(Robot* obj);
bool canMoveForward(Robot* obj);
void pickUpMarker(Robot* obj, bool show_path, bool draw);
void dropMarker(Robot* obj);
int markerCount(Robot* obj);
void leaveTrace(int x, int y);
bool visited(Robot* obj);
void goBack(Robot* obj);
void dfs(Robot* obj, int* home, bool draw, bool show_path, int delay);
