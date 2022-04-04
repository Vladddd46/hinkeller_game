all: install clear

install:
	g++ -I ./inc -c ./src/*
	g++ main.o loadTextures.o -o  sfml-app /usr/local/lib/libsfml-graphics.dylib /usr/local/lib/libsfml-window.dylib /usr/local/lib/libsfml-system.dylib
clear:
	rm -rf main.o loadTextures.o main.hpp.gch loadTextures.hpp.gch
clean: clear
	rm -rf sfml-app