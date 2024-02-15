#ifndef OPS_H
#define OPS_H

#define CTRL_KEY(k) ((k) & 0x1f)
#define SHIFT_KEY(k) ((k) & 0x5f)
#define SPACE_KEY(k) ((k) & 0x20)
#define ENTER 13
#define BACKSPACE 127

/* Key Operations */
char readKey(void);
void keyOperations(void);
int getCursor(int *rows, int *cols);

#endif // OPS_H
