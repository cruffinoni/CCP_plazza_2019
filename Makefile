##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile for the project
##

MAIN_FILE		=	./src/main.cpp
NAME			=	plazza

SRC				=	./src/Kitchen/Kitchen.cpp\
					./src/Kitchen/Cook.cpp\
					./src/Pizza/APizza.cpp

INCLUDE			=	./src/

CXXFLAGS		=	-Wall -Wextra -I $(INCLUDE) -pthread

OBJ				=	$(SRC:.cpp=.o)
OBJ_MAIN		=	$(MAIN_FILE:.cpp=.o)

all: core

core: $(OBJ) $(OBJ_MAIN)
	g++ -o $(NAME) $(OBJ) $(OBJ_MAIN) $(CXXFLAGS)

debug:
	g++ -o $(NAME) $(SRC) $(MAIN_FILE) $(CXXFLAGS) -g

clean:
	rm -f $(OBJ) $(OBJ_MAIN)

fclean:
	rm -f $(OBJ) $(OBJ_MAIN)
	rm -f $(NAME) $(NAME_TEST)

re:	fclean all

.PHONY:	all clean fclean re debug core test
