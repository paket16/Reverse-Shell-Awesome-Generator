# src/Makefile
PREFIX = /usr
BINDIR = $(PREFIX)/bin
TARGET = reverse-shell
SOURCES = main.c reverse_shell.c templates.c
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

.PHONY: all install clean