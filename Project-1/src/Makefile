CC = gcc
CFLAGS = -Wall -std=c99 -Os -fshort-enums
LDFLAGS = -Wall -std=c99 -Os -fshort-enums

MODULES = parser
MAIN_MODULES = Ash
OBJDIR=../obj/build

# Linking
Ash: ../built-in/cd.o ../built-in/cm.o ../built-in/co.o \
	../built-in/ic.o ../built-in/surt.o

# All Modules & Tests
Ash.o: Ash.c ../include/defs.h ../include/built_in.h

# For building built-in commands
.PHONY: build
build:
	$(MAKE) -C ../built-in build

# For keeping Project clean & Makefile updated
renew_dependencies:
	$(CC) -MM *.c

.PHONY: clean veryclean
clean:
	\rm -f *~ *.o *.s
	$(MAKE) -C ../built-in clean
veryclean: clean
	\rm -f $(MAIN_MODULES)
	$(MAKE) -C ../built-in clean
