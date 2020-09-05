# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: akramp <akramp@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/05 18:22:25 by akramp        #+#    #+#                  #
#    Updated: 2020/09/05 18:22:28 by akramp        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra

CC = gcc

SRC = 	./ft_memset.c ./ft_bzero.c \
		./ft_memcpy.c ./ft_memccpy.c \
		./ft_memmove.c ./ft_memchr.c \
		./ft_memcmp.c ./ft_strlen.c \
		./ft_strlcpy.c ./ft_strlcat.c \
		./ft_strchr.c ./ft_strrchr.c \
		./ft_strnstr.c ./ft_strncmp.c \
		./ft_atoi.c ./ft_isalpha.c \
		./ft_isdigit.c ./ft_isalnum.c \
		./ft_isascii.c ./ft_isprint.c \
		./ft_toupper.c ./ft_tolower.c \
		./ft_strdup.c ./ft_calloc.c \
		./ft_substr.c ./ft_strjoin.c \
		./ft_strtrim.c ./ft_split.c \
		./ft_itoa.c ./ft_strmapi.c \
		./ft_putchar_fd.c ./ft_putstr_fd.c \
		./ft_putendl_fd.c ./ft_putnbr_fd.c

SRC_B = ./ft_lstnew_bonus.c ./ft_lstadd_front_bonus.c \
		./ft_islower_bonus.c ./ft_isupper_bonus.c \
		./ft_isspace_bonus.c ./ft_lstsize_bonus.c \
		./ft_lstlast_bonus.c ./ft_lstadd_back_bonus.c \
		./ft_lstiter_bonus.c ./ft_lstclear_bonus.c \
		./ft_lstdelone_bonus.c  ./ft_lstmap_bonus.c

OBJ :=	${SRC:%.c=%.o}

OBJ_B :=	${SRC_B:%.c=%.o}

PINK = 	\033[38;5;206m

PINK2 = \033[38;5;225m

WHITE = \033[38;5;96m

all: $(NAME)

%.o: %.c
	@echo "$(PINK)✿	Compiling $@$(WHITE)\n"
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@echo "$(WHITE)---------------------------------------"
	@echo "$(PINK2)🦄	Libft has been made!$(WHITE)\n"
	@ar -rc $(NAME) $(OBJ)

bonus: $(OBJ_B)
	@ar -rc $(NAME) $(OBJ_B)

clean:
	@echo "$(PINK)🦄	Cleaning ...$(WHITE)\n"
	rm -f $(OBJ) $(OBJ_2) $(OBJ_B)
	rm -f ./*~ ./*#
	@echo "\n$(PINK2)✨	Cleaning Done!\n$(WHITE)"

fclean: clean
	@echo "$(PINK)🦄	Removing $(NAME) ...\n\n$(WHITE)"
	-rm -f $(NAME)
	@echo "\n$(PINK2)✨	Removed $(NAME)!$(WHITE)"
	@echo "$(WHITE)---------------------------------------\n"

re: fclean all
