CC = gcc
CFLAGS = -Wall -std=c99 -Os -fshort-enums
LDFLAGS = -Wall -std=c99 -Os -fshort-enums

MODULES = parser
MAIN_MODULES = Ash

.PHONY: clean veryclean

# Linking
Ash: parser.o

# All Modules & Tests
Ash.o: Ash.c include/defs.h include/parser.h
parser.o: parser.c include/defs.h include/parser.h

# For keeping Project clean & Makefile updated
renew_dependencies:
	$(CC) -MM *.c
clean:
	\rm -f *~ *.o *.s
veryclean: clean
	\rm -f $(MAIN_MODULES)
