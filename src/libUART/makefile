RM 	= rm -rf
LN	= ln -frs
CC 	= gcc
INSTALL	= install

TARGET 	= libUART.so.0.4
CFLAGS 	= -Wall -fPIC
LDFLAGS = -shared -Wl,-soname,$(TARGET)

SRC += unix/error.c
SRC += unix/unix_uart.c
SRC += uart.c
SRC += util.c

OBJ = $(SRC:.c=.o)

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif

all: main

debug: CFLAGS += -g

debug: main

main: $(OBJ)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJ)
	$(LN) $(TARGET) libUART.so

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

install:
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/lib64/
	$(INSTALL) -m 644 libUART.so $(DESTDIR)$(PREFIX)/lib64/
	$(INSTALL) -m 644 $(TARGET) $(DESTDIR)$(PREFIX)/lib64/
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/include/
	$(INSTALL) -m 644 libUART.h $(DESTDIR)$(PREFIX)/include/

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJ) *~
