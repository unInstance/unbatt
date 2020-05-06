CC = cc

CFLAGS  = -std=c99
CFLAGS += -pedantic
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wcast-align
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef

LDFLAGS  = -pthread
LDFLAGS += -lnotify
LDFLAGS += -lgdk_pixbuf-2.0
LDFLAGS += -lgio-2.0
LDFLAGS += -lgobject-2.0
LDFLAGS += -lglib-2.0

INCLUDES  = -I/usr/include/gdk-pixbuf-2.0
INCLUDES += -I/usr/include/libmount
INCLUDES += -I/usr/include/blkid
INCLUDES += -I/usr/include/glib-2.0
INCLUDES += -I/usr/lib64/glib-2.0/include

PREFIX = /usr/local

PROJECT = unbatt

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) *.c -o $(PROJECT)

debug:
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -g *.c -o $(PROJECT)

gdb: debug
	gdb $(PROJECT)

memcheck: debug
	valgrind --leak-check=yes ./$(PROJECT)

memcheck_v: debug
	valgrind --leak-check=yes -v ./$(PROJECT)

memcheck_full: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROJECT)

clean:
	rm $(PROJECT)

install:
	install $(PROJECT) $(PREFIX)/bin/$(PROJECT)

.PHONY: all debug gdb memcheck memcheck_v memcheck_full clean install
