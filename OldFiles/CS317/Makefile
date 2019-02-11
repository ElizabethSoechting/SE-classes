INCLUDE_DIRS = -I/usr/include -I/usr/include/mysql 
LIB_DIRS =  -L /usr/lib64/mysql -L /usr/lib/x86_64-linux-gnu

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lmysqlclient

DRIVER=conntest

HFILES= 
CFILES= conntest.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${DRIVER}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${DRIVER} ${DERIVED} ${GARBAGE}

${DRIVER}:	${OBJS}
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS) $(LIB_DIRS) $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
