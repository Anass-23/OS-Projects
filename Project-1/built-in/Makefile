CC = gcc
CFLAGS = -Wall -std=gnu99 -Os -fshort-enums

SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)

build: $(OBJS)

clean:
	\rm -f *~ *.o *.s *.out
