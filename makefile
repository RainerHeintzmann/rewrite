#  Copyright (c) 1992 Rainer Heintzmann,Blumenhaller Weg 138,4500 Osnabrueck
#  Dieses Makefile generiert das Programm Rewrite.
#
#  Works with gcc + flex + bison on Linux and on Windows (MSYS2 UCRT64 shell).
#  The old 32-bit version is kept as makefile.unix32.orig.

L	= -lm
O	= scan.o sym.o sync.o defs.o syn.o run.o stack.o \
userfkt.o forms.o node.o inout.o \
real.o bool.o complex.o matrix.o vector.o \
fatal.o strsave.o

T	= rewrite

CC	= gcc
CFLAGS	= -Iinclude -DDEBUG -DBISON -std=gnu99 -g
LEX	= flex
YACC	= bison
MV	= cp
RM	= rm -f

all	: $(T)

$(T) : $(O)
	$(CC) -o $(T) $(O) $(L)

scan.c:	scan.l
	$(LEX) -t scan.l > scan.c

syn.c syn.h: syn.y
	$(YACC) -d syn.y
	$(MV) syn.tab.c syn.c
	$(MV) syn.tab.h syn.h

$(O): syn.h

clean:
	$(RM) *.o scan.c syn.c syn.h syn.tab.c syn.tab.h $(T) $(T).exe

.c.o:
	$(CC) $(CFLAGS) -c $<
