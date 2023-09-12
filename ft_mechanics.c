/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mechanics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:46:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/12 14:43:09 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	ft_validate_horizontal(int32_t direction, t_all *data)
{
	size_t	i;
	int32_t	dino_x;
	int32_t	dino_y;
	int32_t	forest_x;
	int32_t	forest_y;

	i = 0;
	dino_y = data->assets->dino->instances->y;
	if (direction == MLX_KEY_LEFT || direction == MLX_KEY_A)
		dino_x = data->assets->dino->instances->x - 110;
	else if (direction == MLX_KEY_RIGHT || direction == MLX_KEY_D)
		dino_x = data->assets->dino->instances->x + 110;
	while (data->assets->forest->instances[i].enabled != false)
	{
		forest_x = data->assets->forest->instances[i].x;
		forest_y = data->assets->forest->instances[i].y;
		if ((dino_x > forest_x && dino_y > forest_y) && \
		(dino_x < (forest_x + 120) && dino_y < (forest_y + 120)))
			return (false);
		i++;
	}
	ft_printf("Moves: %d\n", ++data->moves);
	return (true);
}

int32_t	ft_validate_vertical(int32_t direction, t_all *data)
{
	size_t	i;
	int32_t	dino_x;
	int32_t	dino_y;
	int32_t	forest_x;
	int32_t	forest_y;

	i = 0;
	dino_x = data->assets->dino->instances->x;
	if (direction == MLX_KEY_UP || direction == MLX_KEY_W)
		dino_y = data->assets->dino->instances->y - 110;
	else if (direction == MLX_KEY_DOWN || direction == MLX_KEY_S)
		dino_y = data->assets->dino->instances->y + 110;
	while (i <= data->assets->forest->count)
	{
		forest_x = data->assets->forest->instances[i].x;
		forest_y = data->assets->forest->instances[i].y;
		if ((dino_x > forest_x && dino_y > forest_y) && \
		(dino_x < (forest_x + 120) && dino_y < (forest_y + 120)))
			return (false);
		i++;
	}
	ft_printf("Moves: %d\n", ++data->moves);
	return (true);
}

void	ft_check_collection(t_all *data)
{
	size_t	i;
	int32_t	dino_x;
	int32_t	dino_y;
	int32_t	diamond_x;
	int32_t	diamond_y;

	i = 0;
	dino_x = data->assets->dino->instances->x;
	dino_y = data->assets->dino->instances->y;
	while (i <= data->assets->diamond->count)
	{
		diamond_x = data->assets->diamond->instances[i].x;
		diamond_y = data->assets->diamond->instances[i].y;
		if ((diamond_x > dino_x && diamond_y > dino_y) && \
		(diamond_x < (dino_x + 46) && diamond_y < (dino_y + 46)) \
		&& data->assets->diamond->instances[i].enabled == true)
		{
			data->assets->diamond->instances[i].enabled = false;
			data->d_collected++;
		}
		i++;
	}
	if (data->d_collected == data->assets->diamond->count)
		data->assets->portal->enabled = true;
}

void	ft_hooks(mlx_key_data_t keydata, t_all *data)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	else if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_vertical(keydata.key, data))
		data->assets->dino->instances->y -= 110;
	else if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_vertical(keydata.key, data))
		data->assets->dino->instances->y += 110;
	else if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_horizontal(keydata.key, data))
		data->assets->dino->instances->x -= 113;
	else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_horizontal(keydata.key, data))
		data->assets->dino->instances->x += 113;
	ft_check_collection(data);
}

void	ft_mechanics(mlx_t *mlx, t_asset *assets)
{
	t_all	*all;

	all = ft_calloc(1, sizeof(t_all));
	all->mlx = mlx;
	all->assets = assets;
	all->d_collected = 0;
	mlx_key_hook(mlx, (void *)ft_hooks, (void *)all);
}
