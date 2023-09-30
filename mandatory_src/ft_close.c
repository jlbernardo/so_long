/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:35:33 by julberna          #+#    #+#             */
/*   Updated: 2023/09/30 00:38:48 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_close(t_game **game, int err_code, int i)
{
	if (err_code <= 2)
	{
		i = (*game)->map->y;
		while (--i >= 0)
			free((*game)->map->map[i]);
		i = (*game)->map->y;
		while (--i >= 0)
			free((*game)->map->copy[i]);
		free((*game)->map->map);
		free((*game)->map->copy);
		free((*game)->map);
		free((*game)->count);
	}
	if (err_code <= 1)
	{
		mlx_delete_image((*game)->mlx, (*game)->assets->background);
		mlx_delete_image((*game)->mlx, (*game)->assets->forest);
		mlx_delete_image((*game)->mlx, (*game)->assets->dino);
		mlx_delete_image((*game)->mlx, (*game)->assets->coin);
		mlx_delete_image((*game)->mlx, (*game)->assets->portal);
		mlx_delete_texture((*game)->assets->t_background);
		mlx_delete_texture((*game)->assets->t_forest);
		mlx_delete_texture((*game)->assets->t_dino);
		mlx_delete_texture((*game)->assets->t_coin);
		mlx_delete_texture((*game)->assets->t_portal);
		mlx_delete_texture((*game)->assets->logo);
		free((*game)->assets);
	}
}

void	ft_check_ending(int dino_x, int dino_y, t_game **game)
{
	int	portal_x;
	int	portal_y;

	portal_x = (*game)->assets->portal->instances->x;
	portal_y = (*game)->assets->portal->instances->y;
	if ((*game)->d_collected == (*game)->assets->coin->count)
		(*game)->assets->portal->enabled = true;
	if ((dino_x > portal_x && dino_y > portal_y) && \
		(dino_x < (portal_x + 120) && dino_y < (portal_y + 120)) \
		&& (*game)->assets->portal->enabled == true)
	{
		ft_message(6);
		mlx_close_window((*game)->mlx);
	}
}
