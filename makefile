IDIR =	include
CC=g++
CFLAGS1=-I$(IDIR) -lm -std=c++11
CFLAGS2=-o Holomorph -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

ODIR=obj
SDIR=src
LDIR =../lib

_DEPS = complex.h plot.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_SRC = complex.cpp plot.cpp
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))


$(ODIR)/%.o: %.cpp $(DEPS) $(SRC)
	$(CC) -c -o $@ $< $(CFLAGS1)

holomake: $(OBJ)
	g++ -o $@ $^ $(CFLAGS2)

.PHONY: clean 

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

	