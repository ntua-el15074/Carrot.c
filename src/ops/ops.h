#ifndef OPS_H
#define OPS_H

#define CTRL_KEY(k) ((k) & 0x1f)
#define SHIFT_KEY(k) ((k) & 0x5f)
#define SPACE_KEY(k) ((k) & 0x20)
#define ENTER 13
#define BACKSPACE 127

enum keyPresses {
    ARROW_UP = 1000,
    ARROW_DOWN, 
    ARROW_LEFT,
    ARROW_RIGHT,
    PAGE_UP,
    PAGE_DOWN,
    DELETE_KEY,
    HOME_KEY,
    END_KEY,
};

/* Key Operations */
void moveCursor(int key);
int readKey(void);
void keyOperations(void);
int getCursor(int *rows, int *cols);

#endif // OPS_H
