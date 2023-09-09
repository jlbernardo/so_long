/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:39:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/09 15:11:05 by julberna         ###   ########.fr       */
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
//	ft_mechanics(mlx, assets);
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
	ft_place(map, mlx, assets, 0);
	return (assets);
}

t_asset	*ft_place(t_map *map, mlx_t *mlx, t_asset *asset, int32_t i)
{
	int		x;
	int		y;

	x = 0;
	while (x < map->x * WALL_SIZE)
	{
		y = 0;
		while (y < map->y * WALL_SIZE)
		{
			if (map->map[y / WALL_SIZE][x / WALL_SIZE] == '1')
				asset->img[i++] = mlx_image_to_window(mlx, asset->forest, x, y);
			else if (map->map[y / WALL_SIZE][x / WALL_SIZE] == 'C')
			{
				asset->img[i++] = mlx_image_to_window(mlx, asset->diamond, x + 45, y + 45);
				asset->collectibles++;
			}
			else if (map->map[y / WALL_SIZE][x / WALL_SIZE] == 'P')
				asset->img[i++] = mlx_image_to_window(mlx, asset->dino, x + 45, y + 45);
			else if (map->map[y / WALL_SIZE][x / WALL_SIZE] == 'E')
				asset->img[i++] = mlx_image_to_window(mlx, asset->portal, x + 35, y + 25);
			y += 110;
		}
		x += 113;
	}
	return (asset);
}
