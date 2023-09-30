/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:35:18 by julberna          #+#    #+#             */
/*   Updated: 2023/09/30 00:33:03 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define WALL_SIZE 110

typedef struct s_asset
{
	mlx_texture_t	*logo;
	mlx_texture_t	*t_dino;
	mlx_image_t		*dino;
	mlx_texture_t	*t_forest;
	mlx_image_t		*forest;
	mlx_texture_t	*t_coin;
	mlx_image_t		*coin;
	mlx_texture_t	*t_portal;
	mlx_image_t		*portal;
	mlx_texture_t	*t_background;
	mlx_image_t		*background;
}				t_asset;

typedef struct s_count
{
	int		player;
	int		exit;
	int		collectible;
	int		p_init_x;
	int		p_init_y;
	int		collectable;
	bool	escapable;
}				t_count;

typedef struct s_map
{
	char	**map;
	char	**copy;
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
void		ft_place_1(t_game **game);
void		ft_mechanics(t_game **game);
void		ft_open_window(t_game **game);
void		ft_check_collection(t_game **game);
void		ft_flood(t_game **game, int x, int y);
void		ft_count_lines(char *file, t_game **game);
void		ft_close(t_game **game, int err_code, int i);
void		ft_hooks(mlx_key_data_t keydata, t_game **game);
void		ft_place_2(char pos, t_game **game, int x, int y);
void		ft_check_map_validity(int argc, char *file, t_game **game);
void		ft_create_matrix(char *file, t_game **game, int kind, int i);
void		ft_check_ending(int dino_x, int dino_y, t_game **game);
int			ft_message(int msg_code);
int			ft_validate_boundary(t_game **game, int x, int y);
int			ft_validate_vertical(int direction, t_game **game);
int			ft_validate_horizontal(int direction, t_game **game);

#endif
