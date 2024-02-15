#ifndef ABUF_H
#define ABUF_H

struct abuf {
    char *b;
    int len;
};

#define ABUF_INIT {NULL, 0}

/* ABUF Operations */
void abufAppend(struct abuf *ab, const char *s, int len);
void abufFree(struct abuf *ab);

#endif // ABUF_H
