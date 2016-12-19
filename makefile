IDIR =	include
CC=g++
CFLAGS1=-I$(IDIR) -lm
CFLAGS2=-o Holomorph -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

ODIR=obj
LDIR =../lib

_DEPS = complex.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS1)

holomake: $(OBJ)
	g++ -o $@ $^ $(CFLAGS2)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 