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

all: lib_pacman lib_snake lib_menu

lib_pacman:
	$(CC) -c Pacman/Pacman.cpp ../Core/Object/concrete/Static.cpp ../Core/Object/concrete/Dynamic.cpp ../Core/Object/concrete/Consumable.cpp ../Core/Object/model/AObject.cpp -fpic $(INCLUDE)
	$(CC) -shared Pacman.o Static.o Dynamic.o Consumable.o AObject.o -o arcade_pacman.so
	mv arcade_pacman.so $(LIBDIR)
	

lib_snake:
	$(CC) -c Snake/Snake.cpp ../Core/Object/concrete/Static.cpp ../Core/Object/concrete/Dynamic.cpp ../Core/Object/concrete/Consumable.cpp ../Core/Object/model/AObject.cpp -fpic $(INCLUDE)
	$(CC) -shared  Snake.o Static.o Dynamic.o Consumable.o AObject.o -o arcade_nibbler.so
	mv arcade_nibbler.so $(LIBDIR)
	

lib_menu:
	$(CC) -c Menu/Menu.cpp ../Core/Object/concrete/Static.cpp ../Core/Object/concrete/Dynamic.cpp ../Core/Object/concrete/Consumable.cpp ../Core/Object/model/AObject.cpp -fpic $(INCLUDE)
	$(CC) -shared  Menu.o Static.o Dynamic.o Consumable.o AObject.o -o arcade_menu.so
	mv arcade_menu.so $(LIBDIR)

clean:
	rm -f Menu.o
	rm -f Snake.o
	rm -f Pacman.o Static.o Dynamic.o Consumable.o AObject.o

fclean: clean
	rm -f $(LIBDIR)arcade_pacman.so
	rm -f $(LIBDIR)arcade_nibbler.so
	rm -f $(LIBDIR)arcade_menu.so

re: fclean all

.PHONY: all clean fclean re lib_pacman lib_snake lib_menu