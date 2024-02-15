#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h> 
#include <sys/ioctl.h>
#include <termios.h>

#include "ops.h"
#include "../editor/editor.h"
#include "../screen/screen.h"

struct conf C;

char readKey(void) {
    int nr;
    char c;
    while ((nr = read(STDOUT_FILENO, &c, 1)) != 1) {
        if (nr == -1 && errno != EAGAIN)
            killEditor("Failed to read character!\n");
    }
    return c;
}

void keyOperations (void) {
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

int getCursor(int *rows, int *cols) {

    char buf[32];
    unsigned int i = 0;
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
    while (i < sizeof(buf) - 1) {
        if (read(STDOUT_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    buf[i] = '\0';

    if (buf[0] != '\x1b' || buf[1] != '[') return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

    return 0;
}

