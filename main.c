#include <stdlib.h>
#include <unistd.h> 
#include <ctype.h>
#include <termios.h>

struct termios orig_termios;

void DisableRaw() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void EnableRaw() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(DisableRaw);
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(IXON);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    EnableRaw();
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
        if (!iscntrl(c)) {
            write(STDOUT_FILENO, &c, 1);
        }
    }
    return 0;
}
