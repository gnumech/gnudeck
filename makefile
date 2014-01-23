CC = gcc
SRCFILE1 = src/install.c
SRCFILE2 = src/main.c
SRCFILE3 = src/constants.h
EXECNAME1 = ./construct.exe
EXECNAME2 = run.exe
CFLAGS = -g -Wall
CLIBS = -lcurses
BINDIR = /usr/local/bin
PERMISSION = 0775

build: $(SRCFILE2) $(EXECNAME1)
	$(EXECNAME1)
	$(CC) -o $(EXECNAME2) $(CFLAGS) $(SRCFILE2) $(CLIBS)

configure: $(SRCFILE1)
	$(CC) -o $(EXECNAME1) $(SRCFILE1)
	mkdir home disp home/$(USER) disp/home disp/home/$(USER)

install: $(EXECNAME)
	install -m $(PERMISSION) $(EXECNAME2) $(BINDIR)

clean:
	rm -r $(EXECNAME1) $(EXECNAME2) home disp
