# Makefile
PREFIX = /usr
BINDIR = $(PREFIX)/bin
TARGET = reverse-shell
SOURCES = src/main.c src/reverse_shell.c src/templates.c
CC = gcc
CFLAGS = -O2 -Wall -Wextra
LDFLAGS = -static

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

install: $(TARGET)
	install -D -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)

distclean: clean

.PHONY: all install clean distclean