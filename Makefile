# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: akramp <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/06 13:52:49 by akramp        #+#    #+#                  #
#    Updated: 2020/08/29 12:38:54 by akramp        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
OS = $(shell uname)
CC = gcc
LIBFT = libft/libft.a

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ *✧･ﾟ:*  FLAGS  ✧*:･ﾟ✧: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#

FLAGS = -Wall -Werror -Wextra -fsanitize=address -fno-omit-frame-pointer
FLAGSMLX =  -L. -lmlx -framework OpenGL -framework AppKit
F_MLX_UBUNTU = -I/usr/include -Imlx_linux
FLAGMLX_UBUNTU = -Lmlx_linux -lmlx -lXext -lX11 -lm -lz

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ *✧･ﾟ:* SOURCES ✧*:･ﾟ✧: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#

SRC = bleepbloop.c
SRC2 =	parse_cub3d.c \
		cub_num_parse.c \
		cub_parse.c \
		cub_parse_exit.c \
		cub_parse_init.c \
		cub_parse_map.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c \
		ft_strjoin_c3d.c \
		ft_split_c3d.c \
		ft_calloc_mlx.c \
		ft_bzero_mlx.c \
		./libft/libft.a \
		cub_mlx.c
		
OBJ :=	${SRC:%.c=%.o}
OBJ2 :=	${SRC2:%.c=%.o}

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ *✧･ﾟ:* COLORS ✧*:･ﾟ✧: *✧･ﾟ:* ✧ *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#

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

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ *✧･ﾟ:*  RULES  ✧*:･ﾟ✧: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#

all: $(NAME)

#for apple
%.o: %.c
	$(CC) -Imlx -c $< -o $@

#ubuntu
#%.o: %.c
#	$(CC) -I/usr/include -Imlx_linux -c $< -o $@


	
$(NAME):$(OBJ)
	@echo "\n$(X)$(Y)$(Z) ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ ";
	$(TZE)
	@echo "$(X)$(Y)$(Z)██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗";
	$(TZE)
	@echo "$(X)$(Y)$(Z)██║     ██║   ██║██████╔╝ █████╔╝██║  ██║";
	$(TZE)
	@echo "$(X)$(Y)$(Z)██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║";
	@echo "$(X)$(Y)$(Z)╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝";
	@echo "$(X)$(Y)$(Z) ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝";
	@echo "$(WHITE)☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆"
	@echo "\n$(PINK2)\t🦄 ℂ𝕠𝕞𝕡𝕚𝕝𝕒𝕥𝕚𝕠𝕟 ℂ𝕠𝕞𝕡𝕝𝕖𝕥𝕖\n$(PINK) $(WHITE)"
	@echo "$(WHITE)☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆"
	@$(CC) $(FLAGSMLX) $< -o $(NAME) -I mlxs

$(LIBFT):	
	cd ./libft && $(MAKE) re && $(MAKE) bonus
	
ubuntu: $(OBJ2)
	@echo "\n$(X)$(Y)$(Z) ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ ";
	$(TZE)
	@echo "$(X)$(Y)$(Z)██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗";
	$(TZE)
	@echo "$(X)$(Y)$(Z)██║     ██║   ██║██████╔╝ █████╔╝██║  ██║";
	$(TZE)
	@echo "$(X)$(Y)$(Z)██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║";
	@echo "$(X)$(Y)$(Z)╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝";
	@echo "$(X)$(Y)$(Z) ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝";
	@echo "$(WHITE)☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆"
	@echo "\n$(PINK2)\t🦄 ℂ𝕠𝕞𝕡𝕚𝕝𝕒𝕥𝕚𝕠𝕟 ℂ𝕠𝕞𝕡𝕝𝕖𝕥𝕖\n$(PINK) $(WHITE)"
	@echo "$(WHITE)☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆"
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux $^ -Lmlx_linux -lmlx -lXext -lX11 -lm -lz -o a.out

apple: $(LIBFT) $(OBJ2)
	@echo "\n$(X)$(Y)$(Z) ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ ";
	$(TZE)
	@echo "$(X)$(Y)$(Z)██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗";
	$(TZE)
	@echo "$(X)$(Y)$(Z)██║     ██║   ██║██████╔╝ █████╔╝██║  ██║";
	$(TZE)
	@echo "$(X)$(Y)$(Z)██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║";
	@echo "$(X)$(Y)$(Z)╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝";
	@echo "$(X)$(Y)$(Z) ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝";
	@echo "$(WHITE)☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆"
	@echo "\n$(PINK2)\t🦄 ℂ𝕠𝕞𝕡𝕚𝕝𝕒𝕥𝕚𝕠𝕟 ℂ𝕠𝕞𝕡𝕝𝕖𝕥𝕖\n$(PINK) $(WHITE)"
	@echo "$(WHITE)☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆"
	$(CC) $(FLAGSMLX) $^ -o $(NAME) -I mlxs
	
clean:
	@echo "$(PINK)🦄	Cleaning ...$(WHITE)\n"
	rm -f $(OBJ) $(OBJ2)
	rm -f ./*~ ./*#
	@echo "\n$(PINK2)✨	Cleaning Done!$(WHITE)"

fclean: clean
	@echo "$(PINK)🦄	Removing $(NAME) ...\n$(WHITE)"
	-rm -f $(NAME)
	@echo "\n$(PINK2)✨	Removed $(NAME)!$(WHITE)"

re: fclean all

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#
