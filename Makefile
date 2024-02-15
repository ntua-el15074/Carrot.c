CC = gcc
CFLAGS = -Wall -Wextra -pedantic
CVERSION = c99
OBJDIR = src
SCREENDIR = screen
OPSDIR = ops
EDITORDIR = editor
CARROTDIR = src
EDITOR = $(addprefix $(EDITORDIR)/, editor.c)
OPS = $(addprefix $(OPSDIR)/, ops.c)
SCREEN = $(addprefix $(SCREENDIR)/, screen.c)
OBJS = $(addprefix $(OBJDIR)/, carrot.c $(EDITOR) $(OPS) $(SCREEN))

carrot: 
	$(CC) -o carrot $(OBJS) $(CFLAGS) -std=$(CVERSION)

clean: 
	rm -f carrot
