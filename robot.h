#include <stdbool.h>


void drawRobot(struct Robot* obj, int delay);
int* createHome();
void drawHome(int* coord);
void initMemory(struct Robot* obj);
void forward(struct Robot* obj);
void left(struct Robot* obj);
void right(struct Robot* obj);
bool atMarker(struct Robot* obj);
bool canMoveForward(struct Robot* obj);
void pickUpMarker(struct Robot* obj, bool show_path, bool draw);
void dropMarker(struct Robot* obj);
int markerCount(struct Robot* obj);
void leaveTrace(int x, int y);
bool visited(struct Robot* obj);
void goBack(struct Robot* obj);
void dfs(struct Robot* obj, int* home, bool draw, bool show_path, int delay);
