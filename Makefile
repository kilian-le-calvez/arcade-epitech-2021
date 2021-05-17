##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Makefile
##

all: core graphicals games

core:
	make -C ./src/Core/

graphicals:
	make -C ./src/Lib/

games:
	make -C ./src/Game

clean:
	make clean -C ./src/Core/
	make clean -C ./src/Lib/
	make clean -C ./src/Game/

fclean:	clean
		make fclean -C ./src/Core/
		make fclean -C ./src/Lib/
		make fclean -C ./src/Game/
		rm ./arcade

re:
	make re -C ./src/Core/
	make re -C ./src/Game/
	make re -C ./src/Lib/

.PHONY	:	all clean fclean re core graphicals games
