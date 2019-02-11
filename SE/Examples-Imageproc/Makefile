INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS=

HFILES= 
CFILES= brighten.c

SRCS= ${HFILES} ${CFILES}
COBJS= ${CILES:.c=.o}

all:	brighten brightc.asm

clean:
	-rm -f *.o *.d brighter.ppm brightc.asm
	-rm -f brighten

distclean:
	-rm -f *.o *.d

brighten: brighten.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o $(LIBS)

brightc.asm: brightc.c
	$(CC) -O0 -S $< -o $@

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
