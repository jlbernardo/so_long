/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:35:33 by julberna          #+#    #+#             */
/*   Updated: 2023/09/27 21:36:06 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_close(t_game **game, int err_code, int i)
{
	if (err_code <= 2)
	{
		i = (*game)->map->y;
		while (--i >= 0)
			free((*game)->map->map[i]);
		free((*game)->map->map);
		free((*game)->map);
		free((*game)->count);
	}
	if (err_code <= 1)
	{
		mlx_delete_image((*game)->mlx, (*game)->assets->background);
		mlx_delete_image((*game)->mlx, (*game)->assets->forest);
		mlx_delete_image((*game)->mlx, (*game)->assets->dino);
		mlx_delete_image((*game)->mlx, (*game)->assets->diamond);
		mlx_delete_image((*game)->mlx, (*game)->assets->portal);
		mlx_delete_texture((*game)->assets->t_background);
		mlx_delete_texture((*game)->assets->t_forest);
		mlx_delete_texture((*game)->assets->t_dino);
		mlx_delete_texture((*game)->assets->t_diamond);
		mlx_delete_texture((*game)->assets->t_portal);
		mlx_delete_texture((*game)->assets->logo);
		free((*game)->assets);
	}
}

void	ft_check_ending(int dino_x, int dino_y, t_game **game)
{
	size_t	i;
	int		portal_x;
	int		portal_y;
	int		bat_x;
	int		bat_y;

	i = 0;
	portal_x = (*game)->assets->portal->instances->x;
	portal_y = (*game)->assets->portal->instances->y;
	while (i < (*game)->assets->enemy->count)
	{
		bat_x = (*game)->assets->enemy->instances[i].x;
		bat_y = (*game)->assets->enemy->instances[i].y;
		if ((dino_x > bat_x && dino_y < bat_y) && \
			((dino_x + 45) < (bat_x + 60) && (dino_y + 45) > (bat_y + 39)))
		{
			ft_message(5);
			mlx_close_window((*game)->mlx);
		}
		i++;
	}
	if ((*game)->d_collected == (*game)->assets->diamond->count)
		(*game)->assets->portal->enabled = true;
	if ((dino_x > portal_x && dino_y > portal_y) && \
		(dino_x < (portal_x + 120) && dino_y < (portal_y + 120)) \
		&& (*game)->assets->portal->enabled == true)
	{
		ft_printf("\nTotal moves: %s\n", ft_itoa((*game)->moves));
		ft_message(6);
		mlx_close_window((*game)->mlx);
	}
}
