##
## EPITECH PROJECT, 2021
## Arcade
## File description:
## Makefile
##

NAME	=	arcade

SRC		=	Game/Game.cpp						\
			Core.cpp							\
			main.cpp							\
			Display/Display.cpp					\
			Object/concrete/Consumable.cpp		\
			Object/concrete/Dynamic.cpp			\
			Object/concrete/Static.cpp			\
			Display/DLlib.cpp					\
			Game/DLgame.cpp						\
			Object/model/AObject.cpp

OBJ		=	$(SRC:.cpp=.o)

CPPFLAGS	=  -I ./ -I ./Display/ -I ./Object/ -I ./Enum/ -I ./Object

LDFLAGS	= 	-ldl

RM		=	rm -rf

all		:	$(NAME)


$(NAME) : $(OBJ)
		g++ -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS)
		mv arcade ../../

clean	:
		$(RM) $(OBJ)

fclean	:	clean

re 		: fclean all

.PHONY	:	all clean fclean re