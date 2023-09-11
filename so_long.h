/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:35:18 by julberna          #+#    #+#             */
/*   Updated: 2023/09/10 23:55:02 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"

# define WALL_SIZE 110

typedef struct s_asset
{
	mlx_texture_t	*logo;
	mlx_texture_t	*t_dino;
	mlx_image_t		*dino;
	mlx_texture_t	*t_forest;
	mlx_image_t		*forest;
	mlx_texture_t	*t_diamond;
	mlx_image_t		*diamond;
	mlx_texture_t	*t_portal;
	mlx_image_t		*portal;
	mlx_texture_t	*t_background;
	mlx_image_t		*background;
	int32_t			collectibles;
	int32_t			i_forest[1024];
	int32_t			i_diamond[1024];
}				t_asset;

typedef struct s_essential
{
	int32_t	player;
	int32_t	exit;
	int32_t	collectible;
}				t_essential;

typedef struct s_map
{
	char	**map;
	char	*inline_map;
	int32_t	y;
	int32_t	x;
}				t_map;

typedef struct s_all
{
	mlx_t		*mlx;
	t_map		*map;
	t_essential	*essential;
	t_asset		*assets;
}				t_all;

typedef struct s_temp
{
	int32_t	x;
	int32_t	y;
}				t_temp;

void		ft_mechanics(mlx_t *mlx, t_asset *assets);
t_map		*ft_create_matrix(int fd);
mlx_t		*ft_open_window(t_map *map);
int32_t		ft_count_lines(char *map);
int32_t		ft_check_map_validity(char *file, t_map **map);
int32_t		ft_check_boundary(t_map *map, t_essential item, int x, int y);
t_asset		*ft_load(t_map *map, mlx_t *mlx, t_asset *assets);
t_asset		*ft_place_1(t_map *map, mlx_t *mlx, t_asset *assets);
t_asset		*ft_place_2(char pos, t_asset *assets, mlx_t *mlx, t_temp temp);

#endif
