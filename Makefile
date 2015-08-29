main: main.o
	g++ main.o -o main -std=c++11
main.o:main.cpp
	g++ -c main.cpp -std=c++11
