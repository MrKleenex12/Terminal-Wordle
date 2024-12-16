CXX=	g++
CXXFLAGS= -g -Wall -std=gnu++11
SHELL=	bash

all:main

main:main.o	wordle.o
	$(CXX)	$(CXXFLAGS) main.o wordle.o -o main

main.o:main.cpp
	$(CXX)	$(CXXFLAGS) -c main.cpp

wordle.o:wordle.cpp	wordle.hpp
	$(CXX)	$(CXXFLAGS) -c wordle.cpp

clean:
	rm -f *.o main
