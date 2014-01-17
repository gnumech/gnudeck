CC = gcc
SRCFILE = src/main.c
EXECNAME = a.out
CFLAGS = -g -Wall
CLIBS = -lcurses
BINDIR = /usr/local/bin
PERMISSION = 0775

build: $(SRCFILE)
	$(CC) -o $(EXECNAME) $(CFLAGS) $(SRCFILE) $(CLIBS)
	mkdir home home/$(USER) disp disp/$(USER)

install: $(EXECNAME)
	install -m $(PERMISSION)  $(EXECNAME) $(BINDIR)

clean: $(EXECNAME)
	rm -r $(EXECNAME) home disp
