/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:39:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/28 15:26:50 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_open_window(t_game **game)
{
	int32_t			width;
	int32_t			height;

	width = ((*game)->map->x * 113) + 6;
	height = ((*game)->map->y * 110) + 10;
	if (width > 1920)
		width = 1920;
	if (height > 1080)
		height = 1080;
	(*game)->mlx = mlx_init(width, height, "so_long", false);
	if (!(*game)->mlx)
	{
		mlx_close_window((*game)->mlx);
		ft_close(game, 2, 0);
		exit(ft_message(5));
	}
	(*game)->assets = ft_calloc(1, sizeof(t_asset));
	ft_load(game);
}

void	ft_load(t_game **game)
{
	(*game)->assets->logo = mlx_load_png("./assets/extra/logo.png");
	(*game)->assets->t_forest = mlx_load_png("./assets/extra/forest.png");
	(*game)->assets->forest = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_forest);
	(*game)->assets->t_diamond = mlx_load_png("./assets/diamond/5.png");
	(*game)->assets->diamond = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_diamond);
	(*game)->assets->t_portal = mlx_load_png("./assets/extra/portal.png");
	(*game)->assets->portal = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_portal);
	(*game)->assets->t_dino = mlx_load_png("./assets/dino/idle_1.png");
	(*game)->assets->dino = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_dino);
	(*game)->assets->t_background = mlx_load_png("./assets/extra/bg.png");
	(*game)->assets->background = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_background);
	mlx_set_icon((*game)->mlx, (*game)->assets->logo);
	mlx_image_to_window((*game)->mlx, (*game)->assets->background, 0, 0);
	ft_place_1(game);
}

void	ft_place_1(t_game **game)
{
	int	x;
	int	y;

	x = 0;
	while (x < (*game)->map->y * WALL_SIZE)
	{
		y = 0;
		while (y < (*game)->map->x * WALL_SIZE)
		{
			ft_place_2((*game)->map->map[x / WALL_SIZE][y / WALL_SIZE], \
								game, y, x);
			y += 113;
		}
		x += 110;
	}
	(*game)->assets->portal->enabled = false;
}

void	ft_place_2(char pos, t_game **game, int x, int y)
{
	if (pos == '1')
		mlx_image_to_window((*game)->mlx, (*game)->assets->forest, x, y);
	else if (pos == 'C' || pos == 'c')
		mlx_image_to_window((*game)->mlx, (*game)->assets->diamond, \
							x + 52, y + 60);
	else if (pos == 'P')
		mlx_image_to_window((*game)->mlx, (*game)->assets->dino, \
						x + 45, y + 45);
	else if (pos == 'E' || pos == 'e')
		mlx_image_to_window((*game)->mlx, (*game)->assets->portal, \
						x + 42, y + 25);
}
