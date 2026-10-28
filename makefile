#  Copyright (c) 1992 Rainer Heintzmann,Blumenhaller Weg 138,4500 Osnabrueck
#  Dieses Makefile generiert das Programm Rewrite.
#
#  Works with gcc + flex + bison on Linux and on Windows (MSYS2 UCRT64 shell).
#  The sources are in src/, the program is built here (the tests and the
#  library in inc/ are used from this folder). The old 32-bit version is
#  kept as makefile.unix32.orig.
#
#  make                    the program rewrite
#  make test               the regression tests
#  make install            to PREFIX (/usr/local): bin/rewrite, bin/rewrite-rl,
#                          share/rewrite/{inc,examples,tools}; DESTDIR for packages
#  make uninstall          removes them again
#  make dist               the source tarball rewrite-VERSION.tar.gz (git archive)
#  make bindist            the program with its library as a relocatable tarball
#                          rewrite-VERSION-<system>-<machine>.tar.gz

S	= src
L	= -Wl,-Bstatic -lgmp -Wl,-Bdynamic -lm
ifeq ($(OS),Windows_NT)
# fully static on Windows: no MinGW DLLs (libwinpthread-1.dll) are needed, so
# the program also starts outside the MSYS2 shell
L	= -static -lgmp -lm -lshell32 -Wl,--stack,67108864
endif
O	= $(addprefix $(S)/, scan.o sym.o sync.o defs.o syn.o run.o stack.o \
userfn.o forms.o node.o inout.o \
real.o bool.o complex.o matrix.o vector.o \
fatal.o strsave.o expand.o symfn.o listmatch.o numsort.o exact.o specfun.o apart.o latex.o console.o help.o)

T	= rewrite
VERSION	= 2026.3
EXE	=
SYSTEM	= $(shell uname -s | tr A-Z a-z)
ifeq ($(OS),Windows_NT)
EXE	= .exe
SYSTEM	= windows
endif
PREFIX	= /usr/local
LIBDIR	= $(PREFIX)/share/rewrite

CC	= gcc
# -O2: about twice as fast as without optimization. The trace of DEBUG n
# needs -DDEBUG:  make CFLAGS+=-DDEBUG  (after make clean)
CFLAGS	= -I$(S)/include -O2 -DBISON -std=gnu99 -g -DREWRITE_VERSION='"$(VERSION)"'
ifneq ($(OS),Windows_NT)
# the library of make install (INC "inc/all" from any folder, see src/sync.c)
CFLAGS	+= -DREWRITE_LIBDIR='"$(LIBDIR)"'
endif
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

$(S)/symfn.o: $(S)/symmat.c $(S)/symsolve.c

$(S)/%.o: $(S)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(T)
	sh tests/run_tests.sh

# the library files without the editor and FTP leftovers
install: $(T)
	install -d $(DESTDIR)$(PREFIX)/bin $(DESTDIR)$(LIBDIR)/tools
	install -m 755 $(T)$(EXE) $(DESTDIR)$(PREFIX)/bin/rewrite$(EXE)
	install -m 755 tools/rewrite-rl $(DESTDIR)$(PREFIX)/bin/rewrite-rl
	cp -R inc examples $(DESTDIR)$(LIBDIR)/
	find $(DESTDIR)$(LIBDIR) \( -name 'ws_ftp.log' -o -name '*.bak' -o -name '*~' \) -exec rm -f {} +
	install -m 644 tools/latex_symbols.tsv tools/rewrite_kinds.tsv tools/rewrite_words.txt \
		tools/rewrite.inputrc $(DESTDIR)$(LIBDIR)/tools/
	install -m 755 tools/latex.rlwrap $(DESTDIR)$(LIBDIR)/tools/
	install -m 644 README.md LICENSE $(DESTDIR)$(LIBDIR)/

uninstall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/rewrite$(EXE) $(DESTDIR)$(PREFIX)/bin/rewrite-rl
	$(RM) -r $(DESTDIR)$(LIBDIR)

dist:
	git archive --prefix=rewrite-$(VERSION)/ -o rewrite-$(VERSION).tar.gz HEAD

BINDIST	= rewrite-$(VERSION)-$(SYSTEM)-$(shell uname -m)
bindist: $(T)
	$(RM) -r $(BINDIST)
	$(MAKE) install DESTDIR=$(CURDIR)/$(BINDIST) PREFIX=
	tar czf $(BINDIST).tar.gz $(BINDIST)
	$(RM) -r $(BINDIST)

clean:
	$(RM) $(S)/*.o $(S)/scan.c $(S)/syn.c $(S)/syn.h $(S)/syn.tab.c $(S)/syn.tab.h $(T) $(T).exe
