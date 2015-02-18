CC = g++ -std=c++0x
CFLAGS = -Wall -Werror -ansi -pedantic -g 

all: NBody

NBody: NBody.o Body.o
	$(CC) $(CFLAGS) -o NBody NBody.o Body.o -lsfml-graphics -lsfml-window -lsfml-system

Nbody: Nbody.o Body.o
	$(CC) $(CFLAGS) -o NBody NBody.o Body.o -lsfml-system -lsfml-window -lsfml-graphics


NBody.o: NBody.cpp Body.cpp Body.hpp
	$(CC) $(CFLAGS) -c NBody.cpp

Body.o: Body.cpp Body.hpp
	$(CC) $(CFLAGS) -c Body.cpp

clean:
	rm -rf NBody *.o *.~

