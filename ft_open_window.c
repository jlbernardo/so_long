/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:39:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/10 23:55:45 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_t	*ft_open_window(t_map *map)
{
	int32_t			height;
	int32_t			width;
	mlx_t			*mlx;
	t_asset			*assets;

	width = (map->x * 113) + 6;
	height = (map->y * 110) + 10;
	if (width > 1920)
		width = 1920;
	if (height > 1080)
		height = 1080;
	mlx = mlx_init(width, height, "so_long", false);
	if (!mlx)
	{
		mlx_strerror(MLX_WINFAIL);
		exit(MLX_WINFAIL);
	}
	assets = ft_calloc(1, sizeof(t_asset));
	assets = ft_load(map, mlx, assets);
	ft_mechanics(mlx, assets);
	return (mlx);
}

t_asset	*ft_load(t_map *map, mlx_t *mlx, t_asset *assets)
{
	assets->logo = mlx_load_png("./assets/logo.png");
	assets->t_forest = mlx_load_png("./assets/forest.png");
	assets->forest = mlx_texture_to_image(mlx, assets->t_forest);
	assets->t_diamond = mlx_load_png("./assets/diamond.png");
	assets->diamond = mlx_texture_to_image(mlx, assets->t_diamond);
	assets->t_portal = mlx_load_png("./assets/portal.png");
	assets->portal = mlx_texture_to_image(mlx, assets->t_portal);
	assets->t_dino = mlx_load_png("./assets/dino/idle_1.png");
	assets->dino = mlx_texture_to_image(mlx, assets->t_dino);
	assets->t_background = mlx_load_png("./assets/bg.png");
	assets->background = mlx_texture_to_image(mlx, assets->t_background);
	mlx_set_icon(mlx, assets->logo);
	mlx_image_to_window(mlx, assets->background, 0, 0);
	ft_place_1(map, mlx, assets);
	return (assets);
}

t_asset	*ft_place_2(char pos, t_asset *assets, mlx_t *mlx, t_temp temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (pos == '1')
		assets->i_forest[i++] = mlx_image_to_window(mlx, \
									assets->forest, temp.x, temp.y);
	else if (pos == 'C')
	{
		temp.x += 52;
		temp.y += 60;
		assets->i_diamond[j++] = mlx_image_to_window(mlx, \
									assets->diamond, temp.x, temp.y);
		assets->collectibles++;
	}
	else if (pos == 'P')
		mlx_image_to_window(mlx, assets->dino, temp.x + 45, temp.y + 45);
	else if (pos == 'E')
		mlx_image_to_window(mlx, assets->portal, temp.x + 42, temp.y + 25);
	return (assets);
}

t_asset	*ft_place_1(t_map *map, mlx_t *mlx, t_asset *assets)
{
	t_temp	temp;

	temp.x = 0;
	while (temp.x < map->x * WALL_SIZE)
	{
		temp.y = 0;
		while (temp.y < map->y * WALL_SIZE)
		{
			assets = ft_place_2(map->map[temp.y / WALL_SIZE] \
					[temp.x / WALL_SIZE], assets, mlx, temp);
			temp.y += 110;
		}
		temp.x += 113;
	}
//	assets->portal->enabled = false;
	return (assets);
}
