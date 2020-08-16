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

all: tests 

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

tests: tests.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(RM) tests
	$(RM) *.csv
