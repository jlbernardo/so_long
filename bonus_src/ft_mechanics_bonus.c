/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mechanics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:46:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/29 20:49:17 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_mechanics(t_game **game)
{
	(*game)->count->playable = true;
	mlx_loop_hook((*game)->mlx, (void *)ft_animate, game);
	mlx_key_hook((*game)->mlx, (void *)ft_hooks, (void *)game);
	mlx_loop((*game)->mlx);
	ft_close(game, 1, 0);
	mlx_terminate((*game)->mlx);
	free((*game));
}

void	ft_hooks(mlx_key_data_t keydata, t_game **game)
{
	char	*nbr;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window((*game)->mlx);
	if ((*game)->count->playable == false)
		return ;
	else if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_vertical(keydata.key, game))
		ft_walk_dino(game, 'y', -110);
	else if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_vertical(keydata.key, game))
		ft_walk_dino(game, 'y', 110);
	else if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_horizontal(keydata.key, game))
		ft_walk_dino(game, 'x', -113);
	else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_horizontal(keydata.key, game))
		ft_walk_dino(game, 'x', 113);
	(*game)->assets->str[1]->instances->enabled = false;
	nbr = ft_itoa((*game)->moves);
	(*game)->assets->str[1] = mlx_put_string((*game)->mlx, \
	nbr, (*game)->assets->str[1]->instances->x, 10);
	free(nbr);
	ft_check_collection(game, 0, -1);
}

int	ft_validate_horizontal(int direction, t_game **game)
{
	size_t	i;
	int		dino_x;
	int		dino_y;
	int		forest_x;
	int		forest_y;

	i = 0;
	dino_y = (*game)->assets->dino[0]->instances->y;
	if (direction == MLX_KEY_LEFT || direction == MLX_KEY_A)
		dino_x = (*game)->assets->dino[0]->instances->x - 110;
	else if (direction == MLX_KEY_RIGHT || direction == MLX_KEY_D)
		dino_x = (*game)->assets->dino[0]->instances->x + 110;
	while (i < (*game)->assets->forest->count)
	{
		forest_x = (*game)->assets->forest->instances[i].x;
		forest_y = (*game)->assets->forest->instances[i].y;
		if ((dino_x > forest_x && dino_y > forest_y) && \
		(dino_x < (forest_x + 120) && dino_y < (forest_y + 120)))
			return (false);
		i++;
	}
	(*game)->moves++;
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
	dino_x = (*game)->assets->dino[0]->instances->x;
	if (direction == MLX_KEY_UP || direction == MLX_KEY_W)
		dino_y = (*game)->assets->dino[0]->instances->y - 110;
	else if (direction == MLX_KEY_DOWN || direction == MLX_KEY_S)
		dino_y = (*game)->assets->dino[0]->instances->y + 110;
	while (i < (*game)->assets->forest->count)
	{
		forest_x = (*game)->assets->forest->instances[i].x;
		forest_y = (*game)->assets->forest->instances[i].y;
		if ((dino_x > forest_x && dino_y > forest_y) && \
		(dino_x < (forest_x + 120) && dino_y < (forest_y + 120)))
			return (false);
		i++;
	}
	(*game)->moves++;
	return (true);
}

void	ft_walk_dino(t_game **game, char axis, int pixels)
{
	int	i;

	i = -1;
	if ((*game)->count->playable == true)
	{
		if (axis == 'x')
		{
			while (i++ < 4)
				(*game)->assets->dino[i]->instances->x += pixels;
		}
		else
		{
			while (i++ < 4)
				(*game)->assets->dino[i]->instances->y += pixels;
		}
	}
}
