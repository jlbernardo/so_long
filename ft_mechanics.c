/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mechanics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:46:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/11 20:09:11 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	ft_validate_horizontal(int32_t direction, t_all *data)
{
	int	i;
	int	dino_x;
	int	dino_y;
	int	forest_x;
	int	forest_y;

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
	return (true);
}

int32_t	ft_validate_vertical(int32_t direction, t_all *data)
{
	int	i;
	int	dino_x;
	int	dino_y;
	int	forest_x;
	int	forest_y;

	i = 0;
	dino_x = data->assets->dino->instances->x;
	if (direction == MLX_KEY_UP || direction == MLX_KEY_W)
		dino_y = data->assets->dino->instances->y - 110;
	else if (direction == MLX_KEY_DOWN || direction == MLX_KEY_S)
		dino_y = data->assets->dino->instances->y + 110;
	while (data->assets->forest->instances[i].enabled != false)
	{
		forest_x = data->assets->forest->instances[i].x;
		forest_y = data->assets->forest->instances[i].y;
		if ((dino_x > forest_x && dino_y > forest_y) && \
		(dino_x < (forest_x + 120) && dino_y < (forest_y + 120)))
			return (false);
		i++;
	}
	return (true);
}

void	ft_hooks(mlx_key_data_t keydata, t_all *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(param->mlx);
	else if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_vertical(keydata.key, param))
		param->assets->dino->instances->y -= 110;
	else if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_vertical(keydata.key, param))
		param->assets->dino->instances->y += 110;
	else if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_horizontal(keydata.key, param))
		param->assets->dino->instances->x -= 113;
	else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D) \
			&& keydata.action == MLX_PRESS && \
			ft_validate_horizontal(keydata.key, param))
		param->assets->dino->instances->x += 113;
}

void	ft_mechanics(mlx_t *mlx, t_asset *assets)
{
	t_all	*all;

	all = ft_calloc(1, sizeof(t_all));
	all->mlx = mlx;
	all->assets = assets;
	mlx_key_hook(mlx, (void *)ft_hooks, (void *)all);
}
