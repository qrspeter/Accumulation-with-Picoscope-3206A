# make in windows:
# mingw32-make -f Makefile

flags =  -Wall -fexceptions -g 
# flags =  -Wall -fexceptions -02

CC = g++

all: main
main: main.o
	${CC} -o main.exe main.o  -s .\ps3000a.lib
main.o: main.cpp
	${CC} $(flags) -c main.cpp
clean:
	rm main.o main.exe