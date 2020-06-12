CC = gcc

CFLAGS  = -Wall
CFLAGS += -lm

RM = rm -rf

SRCS  = adev.c
SRCS += tools.c

all: avar

OBJS = $(SRCS:.c:=.o)

avar: tests.c $(SRCS)
	$(CC) $(CFLAGS) -o $@ $< $(SRCS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean
clean:
	$(RM) avar
