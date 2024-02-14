#ifndef EDITOR_H
#define EDITOR_H

#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f)
#define SHIFT_KEY(k) ((k) & 0x5f)
#define SPACE_KEY(k) ((k) & 0x20)
#define ENTER 13
#define BACKSPACE 127

extern struct termios orig_termios;

void killEditor(char* s);
void clearScreen(void);
char readKey(void);
void keyOperations(void);
void DisableRaw(void);
void EnableRaw(void);

#endif // EDITOR_H
