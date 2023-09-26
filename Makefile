# -*- Makefile -*-

NAME = so_long
MLX = ./MLX42/build/libmlx42.a
LIBFT = ./libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

FLAGS = $(MLX) -I ./MLX42/include/MLX42/MLX42.h \
		$(LIBFT) -I ./libft/libft.h -I so_long.h \
		-ldl -lglfw -pthread -lm

SRC = so_long.c ft_check_map_validity.c ft_open_window.c ft_mechanics.c ft_close.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(FLAGS) -o $(NAME)

$(MLX):
	cmake -S ./MLX42 -B ./MLX42/build
	cmake --build ./MLX42/build -j4

$(LIBFT):
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: libclean
	rm -f $(OBJ)

fclean: clean libfclean
	rm -f $(NAME)

libclean:
	make clean -C ./libft

libfclean:
	make fclean -C ./libft

mlxre:
	cmake --build ./MLX42/build --clean-first

re: fclean all

reall: fclean mlxre all

.PHONY: all clean fclean re libclean libfclean mlxre reall