#ifndef EDITOR_H
#define EDITOR_H

#include <termios.h>

struct conf {
    int cx, cy;
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

extern struct conf C;

/* Editor Operations */
void killEditor(char* s);
void initEditor(void);
void DisableRaw(void);
void EnableRaw(void);

#endif // EDITOR_H
