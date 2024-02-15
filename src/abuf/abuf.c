#include <stdlib.h>
#include <string.h>
#include "abuf.h"

void abufAppend(struct abuf *ab, const char *s, int len) {
    char *new = realloc(ab->b, ab->len + len);

    if (new == NULL) return;
    memcpy(&new[ab->len], s, len);

    ab->b = new;
    ab->len += len;
}

void abufFree(struct abuf *ab) {
    free(ab->b);
}
