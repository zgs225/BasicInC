IDIR   = ../include
CC     = gcc
CFLAGS = -I$(IDIR)

ODIR   = obj
LDIR   = ./lib

LIBS   = -lm

_DEPS  = basic.h
DEPS   = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ   = list_parser.o list_parser_test.o
OBJ    = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

list_parser: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
