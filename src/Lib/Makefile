##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Makefile
##

CC			=		g++

CXXFLAGS	=		-Wall -Wextra

INCLUDE		=		-I ../Core -I ../Game -I ../Lib

CPPFLAGS	=		$(INCLUDE)

LIBDIR		=		../../lib/

all: lib_sfml lib_sdl lib_ncurses

lib_sfml:
	$(CC) -c Sfml/Sfml.cpp ../Core/Object/model/AObject.cpp -fpic $(INCLUDE)
	$(CC) -shared Sfml.o AObject.o -o arcade_sfml.so -lsfml-graphics -lsfml-window -lsfml-system
	mv arcade_sfml.so $(LIBDIR)

lib_sdl:
	$(CC) -c Sdl/Sdl.cpp ../Core/Object/model/AObject.cpp -fpic $(INCLUDE)
	$(CC) -shared  Sdl.o AObject.o -o arcade_sdl.so -lSDL2 -lSDL2_image -lSDL2_ttf
	mv arcade_sdl.so $(LIBDIR)

lib_ncurses:
	$(CC) -c Ncurses/Ncurses.cpp ../Core/Object/model/AObject.cpp -fpic $(INCLUDE)
	$(CC) -shared  Ncurses.o AObject.o -o arcade_ncurses.so -lcurses
	mv arcade_ncurses.so $(LIBDIR)

clean:
	rm -f Sfml.o
	rm -f Ncurses.o
	rm -f Sdl.o
	rm -f AObject.o

fclean: clean
	rm -f $(LIBDIR)arcade_sfml.so
	rm -f $(LIBDIR)arcade_sdl.so
	rm -f $(LIBDIR)arcade_ncurses.so

re: fclean all

.PHONY: all clean fclean re lib_sfml lib_sdl lib_ncurses