INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS=

HFILES=  brighten.h
CFILES= imagetest.c brighten.c brightc.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	imagetest brightc.asm

clean:
	-rm -f *.o *.d brighter*.ppm brightc.asm
	-rm -f imagetest

distclean:
	-rm -f *.o *.d

imagetest:	${OBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

brightc.asm: brightc.c
	$(CC) -O0 -S $< -o $@

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
