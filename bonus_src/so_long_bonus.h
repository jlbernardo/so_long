/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:11:26 by julberna          #+#    #+#             */
/*   Updated: 2023/09/29 17:13:01 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <signal.h>

# define WALL_SIZE 110

typedef struct s_asset
{
	mlx_texture_t	*logo;
	mlx_texture_t	*t_dino[4];
	mlx_image_t		*dino[4];
	mlx_texture_t	*t_forest;
	mlx_image_t		*forest;
	mlx_texture_t	*t_coin[6];
	mlx_image_t		*coin[6];
	mlx_texture_t	*t_portal;
	mlx_image_t		*portal;
	mlx_texture_t	*t_background;
	mlx_image_t		*background;
	mlx_texture_t	*t_bat[2];
	mlx_image_t		*bat[2];
	mlx_texture_t	*t_box;
	mlx_image_t		*box;
	mlx_image_t		*moves_str;
	mlx_image_t		*moves_nbr;
	mlx_image_t		*end_str;
	mlx_texture_t	*t_end_bg;
	mlx_image_t		*end_bg;
	mlx_texture_t	*t_you_won;
	mlx_image_t		*you_won;
	mlx_texture_t	*t_game_over;
	mlx_image_t		*game_over;
}				t_asset;

typedef struct s_count
{
	int		player;
	int		exit;
	int		collectible;
	int		p_init_x;
	int		p_init_y;
	int		collectable;
	bool	playable;
	bool	escapable;
}				t_count;

typedef struct s_map
{
	char	**map;
	int		y;
	int		x;
}				t_map;

typedef struct s_game
{
	int			moves;
	mlx_t		*mlx;
	t_map		*map;
	t_count		*count;
	t_asset		*assets;
	size_t		d_collected;
}				t_game;

void		ft_load(t_game **game);
void		ft_animate(t_game **game);
void		ft_mechanics(t_game **game);
void		ft_open_window(t_game **game);
void		ft_load_sprites(t_game **game);
void		ft_flood(t_game **game, int x, int y);
void		ft_place_1(t_game **game, int32_t width);
void		ft_count_lines(char *file, t_game **game);
void		ft_create_matrix(char *file, t_game **game);
void		ft_close(t_game **game, int err_code, int i);
void		ft_hooks(mlx_key_data_t keydata, t_game **game);
void		ft_place_2(char pos, t_game **game, int x, int y);
void		ft_walk_dino(t_game **game, char axis, int pixels);
void		ft_check_ending(int dino_x, int dino_y, t_game **game);
void		ft_check_collection(t_game **game, size_t i, size_t j);
void		ft_check_map_validity(int argc, char *file, t_game **game);
void		ft_free_img(t_game **game, mlx_image_t *img[6], \
						mlx_texture_t *t_img[6], int j);
int			ft_message(int msg_code);
int			ft_validate_boundary(t_game **game, int x, int y);
int			ft_validate_vertical(int direction, t_game **game);
int			ft_validate_horizontal(int direction, t_game **game);

#endif
