IDIR = include
ODIR = .obj
SDIR = src

LIBS=-lm

CC = gcc
CFLAGS = -I $(IDIR)

_DEPS = cube.h load.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o load.o cube.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cube: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 