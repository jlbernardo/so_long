/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:39:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/30 02:40:28 by julberna         ###   ########.fr       */
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
	(*game)->mlx = mlx_init(width, height, "A dino adventure!", false);
	if (!(*game)->mlx)
	{
		mlx_close_window((*game)->mlx);
		ft_close(game, 2);
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
	mlx_image_to_window((*game)->mlx, (*game)->assets->bgs[2], \
	(width - 162), 9);
	(*game)->assets->str[0] = mlx_put_string((*game)->mlx, "Moves: ", \
							(width - 155), 10);
	(*game)->assets->str[1] = mlx_put_string((*game)->mlx, \
								moves, (width - 93), 10);
	free(moves);
}

void	ft_place_2(char pos, t_game **game, int x, int y)
{
	if (pos == '1')
		mlx_image_to_window((*game)->mlx, (*game)->assets->forest, x, y);
	else if (pos == 'B')
		ft_place_sprites(game, 2, x + 27, y + 50);
	else if (pos == 'P')
		ft_place_sprites(game, 4, x + 45, y + 45);
	else if (pos == 'C' || pos == 'c')
		ft_place_sprites(game, 6, x + 52, y + 60);
	else if (pos == 'E' || pos == 'e')
		ft_place_sprites(game, 8, x + 20, y + 20);
}

void	ft_place_sprites(t_game **game, int limit, int x, int y)
{
	int	i;

	i = -1;
	while (++i < limit)
	{
		if (limit == 2)
			mlx_image_to_window((*game)->mlx, (*game)->assets->bat[i], x, y);
		else if (limit == 4)
			mlx_image_to_window((*game)->mlx, (*game)->assets->dino[i], x, y);
		else if (limit == 6)
			mlx_image_to_window((*game)->mlx, (*game)->assets->coin[i], x, y);
		else if (limit == 8)
			mlx_image_to_window((*game)->mlx, (*game)->assets->exit[i], x, y);
		if (i > 0 && limit == 2)
			(*game)->assets->bat[i]->enabled = false;
		else if (i > 0 && limit == 4)
			(*game)->assets->dino[i]->enabled = false;
		else if (i > 0 && limit == 6)
			(*game)->assets->coin[i]->enabled = false;
		else if (limit == 8)
			(*game)->assets->exit[i]->enabled = false;
	}
}
