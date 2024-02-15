#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "screen.h"
#include "../editor/editor.h"
#include "../ops/ops.h"

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

void drawTildes(void) {
    for (int i=0; i<C.screencols; i++)
        write(STDOUT_FILENO, "~\r\n", 3);
}

void clearScreen(void) {
    if (write(STDOUT_FILENO, "\x1b[2J", 4) == -1)
        killEditor("Failed to clear screen\n");
    if (write(STDOUT_FILENO, "\x1b[H", 3) == -1)
        killEditor("Failed to clear screen\n");
}

void refreshScreen(void) {
    if (write(STDOUT_FILENO, "\x1b[2J", 4) == -1)
        killEditor("Failed to clear screen\n");
    if (write(STDOUT_FILENO, "\x1b[H", 3) == -1)
        killEditor("Failed to clear screen\n");

    drawTildes();

    if (write(STDOUT_FILENO, "\x1b[H", 3) == -1)
        killEditor("Failed to clear screen\n");
}
