CC = gcc

RM = rm -rf

SRC_DIR = ../src

SRCS  = $(SRC_DIR)/adev.c
SRCS += $(SRC_DIR)/tools/tools.c

CFLAGS = -O3
#CFLAGS += -mfloat-abi=hard
CFLAGS += -I$(SRC_DIR)
CFLAGS += -Wall
CFLAGS += -lm

all: avar oavar #mvar

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

avar: avar.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@

oavar: oavar.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@

mvar: mvar.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(RM) avar oavar mvar
	$(RM) *.csv
