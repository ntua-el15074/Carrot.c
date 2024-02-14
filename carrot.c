#include <stdlib.h>
// #include <errno.h>
#include <unistd.h> 
// #include <ctype.h>
// #include <stdio.h>
#include <termios.h>

#include "carrot.h"

int main() {

    clearScreen();

    EnableRaw();
    
    while (1) {
        keyOperations();
    }

    exit(EXIT_SUCCESS);

}

