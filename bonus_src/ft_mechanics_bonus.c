/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mechanics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:46:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/25 20:54:46 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_mechanics(t_game **game)
{
	mlx_key_hook((*game)->mlx, (void *)ft_hooks, (void *)game);
	mlx_loop((*game)->mlx);
	ft_close(game, 1, 0);
	mlx_terminate((*game)->mlx);
	free((*game));
}

void	ft_hooks(mlx_key_data_t keydata, t_game **game)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window((*game)->mlx);
		return ;
	}
	else if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_vertical(keydata.key, game))
		(*game)->assets->dino->instances->y -= 110;
	else if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_vertical(keydata.key, game))
		(*game)->assets->dino->instances->y += 110;
	else if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_horizontal(keydata.key, game))
		(*game)->assets->dino->instances->x -= 113;
	else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_horizontal(keydata.key, game))
		(*game)->assets->dino->instances->x += 113;
	ft_check_collection(game);
}

int	ft_validate_horizontal(int direction, t_game **game)
{
	size_t	i;
	int		dino_x;
	int		dino_y;
	int		forest_x;
	int		forest_y;

	i = 0;
	dino_y = (*game)->assets->dino->instances->y;
	if (direction == MLX_KEY_LEFT || direction == MLX_KEY_A)
		dino_x = (*game)->assets->dino->instances->x - 110;
	else if (direction == MLX_KEY_RIGHT || direction == MLX_KEY_D)
		dino_x = (*game)->assets->dino->instances->x + 110;
	while (i < (*game)->assets->forest->count)
	{
		forest_x = (*game)->assets->forest->instances[i].x;
		forest_y = (*game)->assets->forest->instances[i].y;
		if ((dino_x > forest_x && dino_y > forest_y) && \
		(dino_x < (forest_x + 120) && dino_y < (forest_y + 120)))
			return (false);
		i++;
	}
	ft_printf("Moves: %d\n", ++(*game)->moves);
	return (true);
}

int	ft_validate_vertical(int direction, t_game **game)
{
	size_t	i;
	int		dino_x;
	int		dino_y;
	int		forest_x;
	int		forest_y;

	i = 0;
	dino_x = (*game)->assets->dino->instances->x;
	if (direction == MLX_KEY_UP || direction == MLX_KEY_W)
		dino_y = (*game)->assets->dino->instances->y - 110;
	else if (direction == MLX_KEY_DOWN || direction == MLX_KEY_S)
		dino_y = (*game)->assets->dino->instances->y + 110;
	while (i < (*game)->assets->forest->count)
	{
		forest_x = (*game)->assets->forest->instances[i].x;
		forest_y = (*game)->assets->forest->instances[i].y;
		if ((dino_x > forest_x && dino_y > forest_y) && \
		(dino_x < (forest_x + 120) && dino_y < (forest_y + 120)))
			return (false);
		i++;
	}
	ft_printf("Moves: %d\n", ++(*game)->moves);
	return (true);
}

void	ft_check_collection(t_game **game)
{
	size_t	i;
	int		dino_x;
	int		dino_y;
	int		diamond_x;
	int		diamond_y;

	i = 0;
	dino_x = (*game)->assets->dino->instances->x;
	dino_y = (*game)->assets->dino->instances->y;
	while (i < (*game)->assets->diamond->count)
	{
		diamond_x = (*game)->assets->diamond->instances[i].x;
		diamond_y = (*game)->assets->diamond->instances[i].y;
		if ((diamond_x > dino_x && diamond_y > dino_y) && \
		(diamond_x < (dino_x + 46) && diamond_y < (dino_y + 46)) \
		&& (*game)->assets->diamond->instances[i].enabled == true)
		{
			(*game)->assets->diamond->instances[i].enabled = false;
			(*game)->d_collected++;
		}
		i++;
	}
	ft_check_ending(dino_x, dino_y, game);
}
