#include <stdlib.h>
#include <termios.h>

#include <unistd.h> 

#include "ops/ops.h"
#include "editor/editor.h"
#include "screen/screen.h"

int main(void) {

    initEditor();

    refreshScreen();

    EnableRaw();
    
    while (1) {
        keyOperations();
    }

    exit(EXIT_SUCCESS);

}

