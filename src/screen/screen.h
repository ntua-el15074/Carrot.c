#ifndef SCREEN_H
#define SCREEN_H

#include "../abuf/abuf.h"

/* Screen Operations */ 
void drawRows(struct abuf *ab);
int getWindowSize(int *rows, int *cols);
void clearScreen(void);
void refreshScreen(void);

#endif // SCREEN_H
