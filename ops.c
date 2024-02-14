#include <stdlib.h>
#include <errno.h>
#include <unistd.h> 
// #include <ctype.h>
#include <stdio.h>
#include <termios.h>
#include "carrot.h"

struct termios orig_termios;

void killEditor(char* s) {
    perror(s);
    exit(EXIT_FAILURE);
}

void clearScreen() {
    if (write(STDOUT_FILENO, "\x1b[2J", 4) == -1)
        killEditor("Failed to clear screen\n");
    if (write(STDOUT_FILENO, "\x1b[H", 3) == -1)
        killEditor("Failed to clear screen\n");
}

char readKey() {
    int nr;
    char c;
    while ((nr = read(STDOUT_FILENO, &c, 1)) != 1) {
        if (nr == -1 && errno != EAGAIN)
            killEditor("Failed to read character!\n");
    }
    return c;
}

void keyOperations () {
    char c = readKey();
    switch (c) {
        case CTRL_KEY('q'):
            clearScreen();
            exit(EXIT_SUCCESS);
            break;
        case ENTER:
            write(STDOUT_FILENO, "\r\n", 2);
            break;
        case BACKSPACE:
            write(STDOUT_FILENO, "\x1b[D", 3);


        default:
            write(STDOUT_FILENO, &c, 1);
    }
}

void DisableRaw() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        killEditor("Failed to set attr!\n");
}

void EnableRaw() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        killEditor("Failed to set attr!\n");
    if (atexit(DisableRaw) == -1)
        killEditor("Failed to set attr!\n");
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) 
        killEditor("Failed to set attr!\n");
}

