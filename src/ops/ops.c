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

void moveCursor(int key) {
    switch(key) {
        case ARROW_DOWN:
            if (C.cy != C.screenrows - 1) {
                C.cy++;
            }
            break;
        case ARROW_UP:
            if (C.cy != 0) {
                C.cy--;
            }
            break;
        case ARROW_LEFT:
            if (C.cx != 0) {
                C.cx--;
            }
            break;
        case ARROW_RIGHT:
            if (C.cx != C.screencols - 1) {
                C.cx++;
            }
            break;
    }
}

int readKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) killEditor("failed to read");
  }
  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
    if (seq[0] == '[') {
      if (seq[1] >= '0' && seq[1] <= '9') {
        if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
        if (seq[2] == '~') {
          switch (seq[1]) {
            case '1': return HOME_KEY;
            case '3': return DELETE_KEY;
            case '4': return END_KEY;
            case '5': return PAGE_UP;
            case '6': return PAGE_DOWN;
            case '7': return HOME_KEY;
            case '8': return END_KEY;
          }
        }
      } else {
        switch (seq[1]) {
          case 'A': return ARROW_UP;
          case 'B': return ARROW_DOWN;
          case 'C': return ARROW_RIGHT;
          case 'D': return ARROW_LEFT;
          case 'H': return HOME_KEY;
          case 'F': return END_KEY;
        }
      }
    } else if (seq[0] == 'O') {
      switch (seq[1]) {
        case 'H': return HOME_KEY;
        case 'F': return END_KEY;
      }
    }
    return '\x1b';
  } else {
    return c;
  }
}

void keyOperations (void) {
    int c = readKey();
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
            break;
        case PAGE_UP:
        case PAGE_DOWN:
            {
                int times = C.screenrows;
                while (times--)
                    moveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
            }
            break;
        case HOME_KEY:
            C.cx = 0;
            break;
        case END_KEY:
            C.cx = C.screencols - 1;
            break;
        case ARROW_LEFT:
        case ARROW_RIGHT:
        case ARROW_UP:
        case ARROW_DOWN:
            moveCursor(c);
            break;
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

