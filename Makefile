# -*- Makefile -*-

NAME = so_long
MLX = ./.MLX42/build/libmlx42.a
LIBFT = ./libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

FLAGS = $(MLX) -I ./.MLX42/include/MLX42/MLX42.h \
		$(LIBFT) -I ./libft/libft.h -ldl -lglfw -pthread -lm

M_SRC = $(addprefix mandatory_src/, so_long.c ft_check_map_validity.c ft_open_window.c \
		ft_mechanics.c ft_close.c ft_message.c)
B_SRC = $(addprefix bonus_src/, so_long_bonus.c ft_check_map_validity_bonus.c \
		ft_load_sprites_bonus.c	ft_open_window_bonus.c ft_mechanics_bonus.c \
		ft_close_bonus.c ft_message_bonus.c ft_animations_bonus.c ft_ending_bonus.c)
M_OBJ = $(M_SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(M_OBJ)
	$(CC) $(CFLAGS) $(M_OBJ) $(FLAGS) -I ./mandatory_src/so_long.h -o $(NAME)

$(MLX):
	cmake -S ./MLX42 -B ./MLX42/build
	cmake --build ./MLX42/build -j4

$(LIBFT):
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(MLX) $(LIBFT) $(B_OBJ)
	$(CC) $(CFLAGS) $(B_OBJ) $(FLAGS) -I ./bonus_src/so_long_bonus.h -o $(NAME)

clean: libclean
	rm -f $(M_OBJ)
	rm -f $(B_OBJ)

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

.PHONY: all clean fclean re libclean libfclean mlxre reall bonus