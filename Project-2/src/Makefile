CC = gcc
CFLAGS = -Wall -std=gnu99 -Os -fshort-enums
LDFLAGS = -Wall -std=gnu99 -Os -fshort-enums

MAIN_MODULES = perudo
TESTS = tst_dice

# Linking
perudo: perudo.o dice.o bet.o dudo.o # -lpthread -lm

# Modules
perudo.o: perudo.c dice.h bet.h dudo.h
dice.o: dice.c dice.h
bet.o: bet.c dice.h dudo.h bet.h
dudo.o: dudo.c dudo.h

# Testing
tst_dice: tst_dice.o dice.o
tst_dice.o: tst_dice.c dice.h

# For keeping Project clean & Makefile updated
renew_dependencies:
	$(CC) -MM *.c

.PHONY: clean veryclean
clean:
	\rm -f *~ *.o *.s *.out
veryclean: clean
	\rm -f $(MAIN_MODULES) $(TESTS)
