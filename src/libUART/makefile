RM 	= rm -rf
LN	= ln -rs
CC 	= gcc
INSTALL	= install

TARGET 	= libUART.so.0.3
CFLAGS 	= -Wall -fPIC
LDFLAGS = -shared -Wl,-soname,$(TARGET)

SRC += error.c
SRC += error_uart.c
SRC += uart.c

OBJ = $(SRC:.c=.o)

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

all: main

debug: CFLAGS += -g

debug: main

main: $(OBJ)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

install:
	$(LN) $(TARGET) libUART.so
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/lib64/
	$(INSTALL) -m 644 libUART.so $(DESTDIR)$(PREFIX)/lib64/
	$(INSTALL) -m 644 $(TARGET) $(DESTDIR)$(PREFIX)/lib64/
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/include/
	$(INSTALL) -m 644 libUART.h $(DESTDIR)$(PREFIX)/include/

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJ) *~
