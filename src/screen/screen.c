#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "screen.h"
#include "../editor/editor.h"
#include "../ops/ops.h"
#include "../abuf/abuf.h"

struct conf C;

int getWindowSize(int *rows, int *cols) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) == -1) return -1;
        return getCursor(&C.screenrows, &C.screencols);
    } else {
        *rows = ws.ws_row;
        *cols = ws.ws_col;
        return 0;
    }

    return -1;

}

void drawRows(struct abuf *ab) {
    for (int i = 0; i < C.screenrows; i++) {
        if (i == C.screenrows / 3) {
          char welcome[80];
          int welcomelen = snprintf(welcome, sizeof(welcome),
            "%s Carrot editor -- version %s", "\U0001F955", EDITOR_VERSION);
          if (welcomelen > C.screencols) welcomelen = C.screencols;
          int padding = (C.screencols - welcomelen) / 2;
          if (padding) {
            abufAppend(ab, "~", 1);
            padding--;
          }
          while (padding--) abufAppend(ab, " ", 1);
          abufAppend(ab, welcome, welcomelen);
        } else {
            abufAppend(ab, "~", 1);
            abufAppend(ab, "\x1b[K", 3);
            if (i < C.screenrows - 1) {
                abufAppend(ab, "\r\n", 2);
            }
        }
    }
}

void clearScreen(void) {
    struct abuf ab = ABUF_INIT;

    abufAppend(&ab, "\x1b[2J", 4);
    abufAppend(&ab, "\x1b[H", 3);
}

void refreshScreen(void) {
    struct abuf ab = ABUF_INIT;

    abufAppend(&ab, "\x1b[?25l", 6);
    abufAppend(&ab, "\x1b[H", 3);

    drawRows(&ab);
    
    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", C.cy + 1, C.cx + 1);
    abufAppend(&ab, buf, strlen(buf));

    abufAppend(&ab, "\x1b[H", 3);
    abufAppend(&ab, "\x1b[?25h", 6);
    write(STDOUT_FILENO, ab.b, ab.len);

    abufFree(&ab);
}
