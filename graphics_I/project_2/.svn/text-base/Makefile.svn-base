CC = g++

LDLIBS = -I./trimesh/include -L./trimesh/lib.Linux64 -lglut -lGLU -lX11  -lm -L/usr/X11R6/lib

OBJECTS = museum3D.o lamp.o structure.o sculpture.o plant.o

museum3D: $(OBJECTS)
	$(CC) -g $(LDLIBS) $(OBJECTS) -o museum3D -ltrimesh -fopenmp
	make clean
museum3D.o:
	$(CC) -g -c $(LDLIBS) museum3D.cpp -o museum3D.o
lamp.o:
	$(CC) -g -c $(LDLIBS) lamp.cpp -o lamp.o
sculpture.o:
	$(CC) -g -c $(LDLIBS) sculpture.cpp -o sculpture.o
structure.o:
	$(CC) -g -c $(LDLIBS) structure.cpp -o structure.o
plant.o:
	$(CC) -g -c $(LDLIBS) plant.cpp -o plant.o
clean:
	-rm -f *.o