#include <string>
#include <windows.h>

void gotoxy(short int x, short int y);

void setcursor(bool visible, DWORD size);

void drawBorder();

void genPipe(int ind);

void drawPipe(int ind);

void erasePipe(int ind);

void drawBird();

void eraseBird();

//int collision();

int collision(int pP, int gP, int bP);

void gameover();

void updateScore();

void instructions();

void description();

int pressSpace(int bP);

int reaction();

int birdDown(int bP);

void play();