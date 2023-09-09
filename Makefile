# -*- Makefile -*-

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

MAKE_LIBFT = make -C ./libft
FLAGS = ./MLX42/build/libmlx42.a -I ./MLX42/include/MLX42/MLX42.h \
		./libft/libft.a -I ./libft/libft.h -I so_long.h \
		-ldl -lglfw -pthread -lm

SRC = so_long.c ft_check_map_validity.c ft_open_window.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE_LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re