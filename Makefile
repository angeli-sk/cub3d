# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: akramp <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/06 13:52:49 by akramp        #+#    #+#                  #
#    Updated: 2020/09/03 20:30:55 by akramp        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
OS = $(shell uname)
CC = gcc
LIBFT = libft/libft.a
MLX = libmlx.dylib

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ *✧･ﾟ:*  FLAGS  ✧*:･ﾟ✧: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#

FLAGS = -Wall -Werror -Wextra

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ *✧･ﾟ:* SOURCES ✧*:･ﾟ✧: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#

_SRC =	parse_cub3d.c \
		cub_num_parse.c \
		cub_parse.c \
		cub_parse_exit.c \
		cub_parse_init.c \
		cub_parse_map.c \
		ft_strjoin_c3d.c \
		ft_split_c3d.c \
		ft_calloc_mlx.c \
		ft_bzero_mlx.c \
		cub_mlx.c \
		bitmappers.c \
		cub_sprite.c \
		map_validate.c \
		walksies.c \
		calc.c \
		mlx_utility.c \
		verline.c \
		keys.c \
		file_checkor.c \
		main.c

SRC = $(addprefix SRCS/, $(_SRC)) \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c
OBJ :=	${SRC:%.c=%.o}

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

%.o: %.c
	$(CC) -Imlx -c $< -o $@

$(NAME): $(LIBFT) $(OBJ) $(MLX)
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
	$(CC) $(FLAGS) $(MLX) $(LIBFT) $^ -o $(NAME) -I mlxs -O3

$(LIBFT):
	cd ./libft && $(MAKE) re && $(MAKE) bonus

$(MLX):
	cd mlx && $(MAKE)
	mv mlx/$(MLX) .

clean:
	@echo "$(PINK)🦄	Cleaning ...$(WHITE)\n"
	rm -f $(OBJ)
	cd ./libft && $(MAKE) clean
	cd ./mlx && $(MAKE) clean
	rm -f ./*~ ./*#
	@echo "\n$(PINK2)✨	Cleaning Done!$(WHITE)"

fclean: clean
	@echo "$(PINK)🦄	Removing $(NAME) ...\n$(WHITE)"
	rm -f $(NAME)
	cd ./libft && $(MAKE) fclean
	rm -f $(MLX)
	rm -f screenshot.bmp libft.a
	@echo "\n$(PINK2)✨	Removed $(NAME)!$(WHITE)"

re: fclean all

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#
