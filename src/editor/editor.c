#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "editor.h"
#include "../screen/screen.h"

void killEditor(char* s) {
    clearScreen();
    perror(s);
    exit(EXIT_FAILURE);
}

void DisableRaw(void) {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &C.orig_termios) == -1)
        killEditor("Failed to set attr!\n");
}

void EnableRaw(void) {
    if (tcgetattr(STDIN_FILENO, &C.orig_termios) == -1)
        killEditor("Failed to set attr!\n");
    if (atexit(DisableRaw) == -1)
        killEditor("Failed to set attr!\n");
    struct termios raw = C.orig_termios;
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) 
        killEditor("Failed to set attr!\n");
}

void initEditor(void) {
    if (getWindowSize(&C.screenrows, &C.screencols) == -1)
        killEditor("Failed to get window size!\n");
}

