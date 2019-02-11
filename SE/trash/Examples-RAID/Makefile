INCLUDE_DIRS = 
LIB_DIRS = 

CDEFS=
CFLAGS= -O2 -g $(INCLUDE_DIRS) $(CDEFS)
#LIBS= -lpthread
LIBS=

PRODUCT=raidops

HFILES=
CFILES= raidops.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

${PRODUCT}:	${OBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
