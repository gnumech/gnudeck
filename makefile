CC = gcc
SRCFILE = src/main.c
EXECNAME = gnudeck.run
CFLAGS = -g -Wall
BINDIR = /usr/local/bin
PERMISSION = 0775

build: $(SRCFILE)
	$(CC) -o $(EXECNAME) $(CFLAGS) $(SRCFILE)

install: $(EXECNAME)
	install -m $(PERMISSION)  $(EXECNAME) $(BINDIR)

clean: $(EXECNAME)
	rm $(EXECNAME)
