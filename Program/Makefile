CC = g++
CFLAGS = -g -Wall

all: main.o searchfilelib.o
	$(CC) $(CFLAGS) -o main main.o searchfilelib.o

main.o: main.cpp searchlib.h
	$(CC) $(CFLAGS) -c main.cpp

searchfilelib.o: searchlib.h

clean:
	rm *.o main