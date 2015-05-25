CC=gcc
CFLAGS=-g
INCLUDES=$(addprefix -I,$(shell find . -not -iwholename "*.git*" -type d -print))
LDPATHS=$(addprefix -L,$(shell find . -not -iwholename "*.git*" -type d -print))
LDLIBS=-lpm
LDFLAGS=$(LDPATHS) $(LDLIBS)
PROGNAME=./a1test

build: a1test.c
	$(CC) $(CFLAGS) $(INCLUDES) a1test.c $(LDFLAGS) -o $(PROGNAME)

test: build
	$(PROGNAME)

