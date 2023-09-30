/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:35:33 by julberna          #+#    #+#             */
/*   Updated: 2023/09/30 03:04:03 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_assets(t_game **game, mlx_image_t *img, mlx_texture_t *t_img);

void	ft_close(t_game **game, int err_code, int i)
{
	if (err_code <= 2)
	{
		while (++i < (*game)->map->y)
		{
			free((*game)->map->map[i]);
			free((*game)->map->copy[i]);
		}
		free((*game)->map->map);
		free((*game)->map->copy);
		free((*game)->map);
		free((*game)->count);
	}
	if (err_code <= 1)
	{
		ft_free_assets(game, (*game)->assets->background, \
				(*game)->assets->t_background);
		ft_free_assets(game, (*game)->assets->forest, \
				(*game)->assets->t_forest);
		ft_free_assets(game, (*game)->assets->dino, (*game)->assets->t_dino);
		ft_free_assets(game, (*game)->assets->coin, (*game)->assets->t_coin);
		ft_free_assets(game, (*game)->assets->portal, \
				(*game)->assets->t_portal);
		mlx_delete_texture((*game)->assets->logo);
		free((*game)->assets);
	}
}

void	ft_free_assets(t_game **game, mlx_image_t *img,	mlx_texture_t *t_img)
{
	mlx_delete_image((*game)->mlx, img);
	mlx_delete_texture(t_img);
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
