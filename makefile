#  Copyright (c) 1992 Rainer Heintzmann,Blumenhaller Weg 138,4500 Osnabrueck
#  Dieses Makefile generiert das Programm Rewrite.

#	UNIX-makefile

L	= -Llib -lm 
O	= scan.o sym.o sync.o defs.o syn.o run.o stack.o \
userfkt.o forms.o node.o inout.o \
real.o bool.o complex.o matrix.o vector.o \
fatal.o strsave.o
# lib/tload.o lib/tsearch.o lib/bsearch.o lib/strsave.o lib/alloca.o \

T	= rewrite

CFLAGS	= -Iinclude -DDEBUG -DBISON  -std=gnu99
# CFLAGS	= -Iinclude -DDEBUG -DBISON -m32 

CC	= gcc -m32 -g 
# LN	= gcc -m32 -o 
LN	= gcc  -m32 -o 
LEX	= flex
MV	= cp
RM	= rm 
YACC	= bison 

all	: $(T)

rewrite : $(O) 
	$(LN) rewrite $(O) $(L)

scan.c:	scan.l
	$(LEX) -t scan.l > scan.c

syn.c: syn.tab.c
	$(MV) syn.tab.c syn.c
	$(MV) syn.tab.h syn.h
	touch syn.c syn.h

syn.tab.c: syn.y
	$(YACC) -d syn.y

sync.o: sync.c sync.h syn.c

scan.o: syn.c run.h sym.h scan.c

syn.o: run.h sym.h

sym.o: run.h syn.c sym.h

forms.o: forms.c forms.h syn.c

stack.o: stack.h

userfkt.o: userfkt.h sym.h

run.o: stack.c syn.c

clean:
	$(RM) *.o scan.c syn.c syn.h y.tab.* y.tok.*
	$(RM) $(T)

.c.o:
	$(CC) $(CFLAGS) -c $<
