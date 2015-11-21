CC = g++

LDLIBS = -lglut -lGLU -lX11  -lm -L/usr/X11R6/lib
OBJECTS = brick.o brick3D.o sphere.o base.o vector.o bonus.o

brick3D: $(OBJECTS)
	$(CC) -g $(LDLIBS) $(OBJECTS) -o brick3D
	make clean
brick.o:
	$(CC) -g -c $(LDLIBS) brick.cpp -o brick.o
brick3D.o:
	$(CC) -g -c $(LDLIBS) brick3D.cpp -o brick3D.o
sphere.o:
	$(CC) -g -c $(LDLIBS) sphere.cpp -o sphere.o
base.o:
	$(CC) -g -c $(LDLIBS) base.cpp -o base.o
vector.o:
	$(CC) -g -c $(LDLIBS) vector.cpp -o vector.o
bonus.o:
	$(CC) -g -c $(LDLIBS) bonus.cpp -o bonus.o
clean:
	-rm -f *.o