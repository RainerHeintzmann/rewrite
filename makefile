#  Copyright (c) 1992 Rainer Heintzmann,Blumenhaller Weg 138,4500 Osnabrueck
#  Dieses Makefile generiert das Programm Rewrite.
#
#  Works with gcc + flex + bison on Linux and on Windows (MSYS2 UCRT64 shell).
#  The sources are in src/, the program is built here (the tests and the
#  library in inc/ are used from this folder). The old 32-bit version is
#  kept as makefile.unix32.orig.

S	= src
L	= -Wl,-Bstatic -lgmp -Wl,-Bdynamic -lm
O	= $(addprefix $(S)/, scan.o sym.o sync.o defs.o syn.o run.o stack.o \
userfkt.o forms.o node.o inout.o \
real.o bool.o complex.o matrix.o vector.o \
fatal.o strsave.o expand.o symfkt.o listmatch.o numsort.o exact.o specfun.o apart.o)

T	= rewrite

CC	= gcc
CFLAGS	= -I$(S)/include -DDEBUG -DBISON -std=gnu99 -g
LEX	= flex
YACC	= bison
MV	= cp
RM	= rm -f

all	: $(T)

$(T) : $(O)
	$(CC) -o $(T) $(O) $(L)

$(S)/scan.c:	$(S)/scan.l
	$(LEX) -t $(S)/scan.l > $(S)/scan.c

$(S)/syn.c $(S)/syn.h: $(S)/syn.y
	cd $(S) && $(YACC) -d syn.y && $(MV) syn.tab.c syn.c && $(MV) syn.tab.h syn.h

$(O): $(S)/syn.h

$(S)/symfkt.o: $(S)/symmat.c

$(S)/%.o: $(S)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(T)
	sh tests/run_tests.sh

clean:
	$(RM) $(S)/*.o $(S)/scan.c $(S)/syn.c $(S)/syn.h $(S)/syn.tab.c $(S)/syn.tab.h $(T) $(T).exe
