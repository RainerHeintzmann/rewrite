CFLAGS	= -I../include
RANLIB	= ranlib
CC	= gcc -g

l	= libocal.a
o	= $(tsearch)

tsearch	= alloca.o fatal.o strsave.o tload.o tsearch.o

all:		$l
clean:				; rm -f *.o
clobber:	clean		; rm -f $l

$l:		$o		; ar rv $@ $?
				  $(RANLIB) $@

$(tsearch):	../include/tsearch.h

