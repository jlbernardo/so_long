/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:39:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/30 00:41:15 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
		exit(ft_message(4));
	}
	(*game)->assets = ft_calloc(1, sizeof(t_asset));
	ft_load_sprites(game);
	ft_place_1(game, width);
}

void	ft_place_1(t_game **game, int32_t width)
{
	int		x;
	int		y;
	char	*moves;

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
	moves = ft_itoa((*game)->moves);
	mlx_image_to_window((*game)->mlx, (*game)->assets->bgs[2], (width - 162), 9);
	(*game)->assets->str[0] = mlx_put_string((*game)->mlx, "Moves: ", \
							(width - 155), 10);
	(*game)->assets->str[1] = mlx_put_string((*game)->mlx, \
								moves, (width - 93), 10);
	free(moves);
}

void	ft_place_2(char pos, t_game **game, int x, int y)
{
	int	i;

	i = -1;
	if (pos == '1')
		mlx_image_to_window((*game)->mlx, (*game)->assets->forest, x, y);
	else if (pos == 'C' || pos == 'c')
	{
		while (++i < 6)
		{
			mlx_image_to_window((*game)->mlx, (*game)->assets->coin[i], \
			x + 52, y + 60);
			if (i > 0)
				(*game)->assets->coin[i]->enabled = false;
		}
	}
	else if (pos == 'P')
	{
		while (++i < 4)
		{
			mlx_image_to_window((*game)->mlx, (*game)->assets->dino[i], \
			x + 45, y + 45);
			if (i > 0)
				(*game)->assets->dino[i]->enabled = false;
		}
	}
	else if (pos == 'E' || pos == 'e')
	{
		while (++i < 8)
		{
			mlx_image_to_window((*game)->mlx, (*game)->assets->exit[i], \
			x + 20, y + 20);
			(*game)->assets->exit[i]->enabled = false;
		}
	}
	else if (pos == 'B')
	{
		while (++i < 2)
		{
			mlx_image_to_window((*game)->mlx, (*game)->assets->bat[i], \
			x + 27, y + 50);
			if (i > 0)
				(*game)->assets->bat[i]->enabled = false;
		}
	}
}
