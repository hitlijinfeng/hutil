CC	= gcc -Wall
CFLAGS	= -g -O2
LDFLAGS	= `pkg-config --libs libpci`

BIN	= lsdxio
sbindir	= /usr/sbin

all: $(BIN)

clean:
	rm -f *.o $(BIN)

distclean: clean
	rm -f *~ \#*

install: all
	install -m 755 $(BIN) $(sbindir)

.o:
	$(CC) $(LDFLAGS) -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -o $@ $<

.c:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

