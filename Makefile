SRC = main.cpp

all: build

build:
	g++ $(SRC) -o main

clean:
	rm -f main
