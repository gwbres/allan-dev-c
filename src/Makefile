CC = gcc

CFLAGS  = -Wall
CFLAGS += -lm

RM = rm -rf

avar: tests.c adev.c tools.c
	$(CC) $(CFLAGS) -o $@ $< adev.c tools.c

.PHONY: clean
clean:
	$(RM) avar
