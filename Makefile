all: main

main: main.o input.o calculate.o
	g++ main.o input.o calculate.o -o geometry.exe

main.o: main.cpp
	g++ -c main.cpp

input.o: input.cpp
	g++ -c input.cpp

calculate.o: calculate.cpp
	g++ -c calculate.cpp

clean:
	rm -rf *.o main