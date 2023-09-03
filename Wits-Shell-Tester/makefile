CC = gcc
CFLAGS = -Wall -Werror

.PHONY: all clean

all: witsshell

witsshell: witsshell.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f witsshell
