c++ := g++

all: clear compile

clear:
	clear

compile:
	g++ --std=c++20 src/*.cpp -o bin/ratc

run:
	./bin/ratc