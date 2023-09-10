/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mechanics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:46:03 by julberna          #+#    #+#             */
/*   Updated: 2023/09/09 22:18:18 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_hooks(mlx_key_data_t keydata, t_all *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(param->mlx);
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		param->assets->dino->instances->y -= 110;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		param->assets->dino->instances->y += 110;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		param->assets->dino->instances->x -= 113;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
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
