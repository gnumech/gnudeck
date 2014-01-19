CC = gcc
SRCFILE = src/main.c
EXECNAME = run.exe
CFLAGS = -g -Wall
CLIBS = -lcurses
BINDIR = /usr/local/bin
PERMISSION = 0775

build: $(SRCFILE)
	$(CC) -o $(EXECNAME) $(CFLAGS) $(SRCFILE) $(CLIBS)
	mkdir home home/$(USER) disp disp/home disp/home/$(USER)

install: $(EXECNAME)
	install -m $(PERMISSION)  $(EXECNAME) $(BINDIR)

clean:
	rm -r $(EXECNAME) home disp
