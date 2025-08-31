CC=cc
CFLAGS=-Wall -Werror
LIBS=-lncurses -lm

.PHONY: all
all: viit

viit: viit.c
	$(CC) $(CFLAGS) -o viit viit.c $(LIBS)

install:
	install -m 755 viit /usr/bin

