# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: akramp <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/06 13:52:49 by akramp        #+#    #+#                  #
#    Updated: 2020/05/06 16:19:35 by akramp        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

FLAGS = -Wall -Werror -Wextra

FLAGSMLX =  -Lmlx -lmlx -framework OpenGL -framework AppKit

CC = gcc

SRC = cub3d.c

OBJ :=	${SRC:%.c=%.o}

PINK	= 	\033[38;5;206m
PINK2	= \033[38;5;225m
WHITE	= \033[38;5;96m
X		= \033[38;5;
Y		= 1
Z		= m
TZE		= $(eval Y=$(shell echo $$((($(Y)%15)+1))))
LI		= 0
BLUE = \033[38;5;33m
RED = \033[38;5;160m
GREEN = \033[38;5;112m
RANDOM := $$((RANDOM % 10))

all: $(NAME)
	
%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -L. -lmlx -framework OpenGL -framework AppKit $< -o $(NAME) -I mlx

# $(NAME):say $(OBJ) $(OBJ_2)
# 	@ar -rc $(NAME) $(OBJ) $(OBJ_2)
# 	@echo "$(WHITE)--------------------------------"
# 	@echo "$(PINK2)✨	Compilation Done! $(WHITE)"

say:
	@echo "\n$(X)$(Y)$(Z)  _       ___     ___      ___   _____  ";
	$(TZE)
	@echo "$(X)$(Y)$(Z) | |     |_ _|   | _ )    | __| |_   _| ";
	$(TZE)
	@echo "$(X)$(Y)$(Z) | |__    | |    | _ \    | _|    | |   ";
	$(TZE)
	@echo "$(X)$(Y)$(Z) |____|  |___|   |___/   _|_|_   _|_|_  ";
	@echo "$(PINK)|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_| \"\"\" |_|\"\"\"\"\"| ";
	@echo "\`-0-0-'\"\`-0-0-'\"\`-0-0-'\"\`-0-0-'\"\`-0-0-' ";
	@echo "\n$(PINK2)🦄	Library Compilation $(PINK) $(WHITE)"
	@echo "$(WHITE)--------------------------------\n"

clean:
	@echo "$(PINK)🦄	Cleaning ...$(WHITE)\n"
	rm -f $(OBJ) $(OBJ_2) $(OBJ_B)
	rm -f ./*~ ./*#
	@echo "\n$(PINK2)✨	Cleaning Done!$(WHITE)"
	
fclean: clean
	@echo "$(PINK)🦄	Removing $(NAME) ...\n$(WHITE)"
	-rm -f $(NAME)
	@echo "\n$(PINK2)✨	Removed $(NAME)!$(WHITE)"
