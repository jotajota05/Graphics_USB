CC = g++

LDLIBS = -I./trimesh/include -L./trimesh/lib.Linux64 -lglut -lGLU -lX11  -lm -L/usr/X11R6/lib

OBJECTS = shooter3D.o structure.o base.o box.o rifle.o objetive.o railing.o bullet.o lamp.o shelf.o sculpture.o

shooter3D: $(OBJECTS)
	$(CC) -g $(LDLIBS) $(OBJECTS) -o shooter3D -ltrimesh -fopenmp
	make clean
shooter3D.o:
	$(CC) -g -c $(LDLIBS) shooter3D.cpp -o shooter3D.o
structure.o:
	$(CC) -g -c $(LDLIBS) structure.cpp -o structure.o
base.o:
	$(CC) -g -c $(LDLIBS) base.cpp -o base.o
box.o:
	$(CC) -g -c $(LDLIBS) box.cpp -o box.o
rifle.o:
	$(CC) -g -c $(LDLIBS) rifle.cpp -o rifle.o
objetive.o:
	$(CC) -g -c $(LDLIBS) objetive.cpp -o objetive.o
railing.o:
	$(CC) -g -c $(LDLIBS) railing.cpp -o railing.o
bullet.o:
	$(CC) -g -c $(LDLIBS) bullet.cpp -o bullet.o
lamp.o:
	$(CC) -g -c $(LDLIBS) lamp.cpp -o lamp.o
shelf.o:
	$(CC) -g -c $(LDLIBS) shelf.cpp -o shelf.o
sculpture.o:
	$(CC) -g -c $(LDLIBS) sculpture.cpp -o sculpture.o
clean:
	-rm -f *.o