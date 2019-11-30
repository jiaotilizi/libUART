RM 	= rm -rf
LN	= ln -rs
CC 	= gcc

TARGET 	= libUART_demo
CFLAGS 	= -Wall -I./../libUART
LDFLAGS = -L./../libUART -lUART

SRC += main.c

OBJ = $(SRC:.c=.o)

all: main

debug: CFLAGS += -g

debug: main

main: $(OBJ)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJ) *~
