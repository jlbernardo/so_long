/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 02:30:24 by julberna          #+#    #+#             */
/*   Updated: 2023/09/30 02:36:27 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_close(t_game **game, int err_code)
{
	if (err_code <= 2)
		ft_free_matrix(game);
	if (err_code <= 1)
		ft_free_assets(game);
}

void	ft_free_matrix(t_game **game)
{
	int	i;

	i = 0;
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

void	ft_free_assets(t_game **game)
{
	ft_free_img(game, (*game)->assets->bat, (*game)->assets->t_bat, 2);
	ft_free_img(game, (*game)->assets->dino, (*game)->assets->t_dino, 4);
	ft_free_img(game, (*game)->assets->coin, (*game)->assets->t_coin, 6);
	ft_free_img(game, (*game)->assets->bgs, (*game)->assets->t_bgs, 3);
	ft_free_img(game, (*game)->assets->msg, (*game)->assets->t_msg, 2);
	ft_free_img(game, (*game)->assets->exit, (*game)->assets->t_exit, 8);
	mlx_delete_image((*game)->mlx, (*game)->assets->forest);
	mlx_delete_image((*game)->mlx, (*game)->assets->str[0]);
	mlx_delete_image((*game)->mlx, (*game)->assets->str[1]);
	mlx_delete_image((*game)->mlx, (*game)->assets->str[2]);
	mlx_delete_texture((*game)->assets->t_forest);
	mlx_delete_texture((*game)->assets->logo);
	free((*game)->assets);
}

void	ft_free_img(t_game **game, mlx_image_t *img[8], \
					mlx_texture_t *t_img[8], int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		mlx_delete_image((*game)->mlx, img[i]);
		i++;
	}
	i = 0;
	while (i < j)
	{
		mlx_delete_texture(t_img[i]);
		i++;
	}
}
