/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:45:40 by julberna          #+#    #+#             */
/*   Updated: 2023/09/29 21:44:31 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_load_dino(t_game **game)
{
	int	i;

	i = 0;
	(*game)->assets->t_dino[0] = mlx_load_png("./assets/dino/idle_1.png");
	(*game)->assets->t_dino[1] = mlx_load_png("./assets/dino/idle_2.png");
	(*game)->assets->t_dino[2] = mlx_load_png("./assets/dino/idle_3.png");
	(*game)->assets->t_dino[3] = mlx_load_png("./assets/dino/idle_4.png");
	while (i < 4)
	{
		(*game)->assets->dino[i] = mlx_texture_to_image((*game)->mlx, \
		(*game)->assets->t_dino[i]);
		if (i > 0)
			(*game)->assets->dino[i]->enabled = false;
		i++;
	}
}

void	ft_load_coin(t_game **game)
{
	int	i;

	i = 0;
	(*game)->assets->t_coin[0] = mlx_load_png("./assets/coin/1.png");
	(*game)->assets->t_coin[1] = mlx_load_png("./assets/coin/2.png");
	(*game)->assets->t_coin[2] = mlx_load_png("./assets/coin/3.png");
	(*game)->assets->t_coin[3] = mlx_load_png("./assets/coin/4.png");
	(*game)->assets->t_coin[4] = mlx_load_png("./assets/coin/5.png");
	(*game)->assets->t_coin[5] = mlx_load_png("./assets/coin/6.png");
	while (i < 6)
	{
		(*game)->assets->coin[i] = mlx_texture_to_image((*game)->mlx, \
		(*game)->assets->t_coin[i]);
		if (i > 0)
			(*game)->assets->coin[i]->enabled = false;
		i++;
	}
}

void	ft_load_bat(t_game **game)
{
	int	i;

	i = 0;
	(*game)->assets->t_bat[0] = mlx_load_png("./assets/bat/1.png");
	(*game)->assets->t_bat[1] = mlx_load_png("./assets/bat/2.png");
	while (i < 2)
	{
		(*game)->assets->bat[i] = mlx_texture_to_image((*game)->mlx, \
		(*game)->assets->t_bat[i]);
		if (i > 0)
			(*game)->assets->bat[i]->enabled = false;
		i++;
	}
}

void	ft_load_portal(t_game **game)
{
	int	i;

	i = 0;
	(*game)->assets->t_exit[0] = mlx_load_png("./assets/portal/1.png");
	(*game)->assets->t_exit[1] = mlx_load_png("./assets/portal/2.png");
	(*game)->assets->t_exit[2] = mlx_load_png("./assets/portal/3.png");
	(*game)->assets->t_exit[3] = mlx_load_png("./assets/portal/4.png");
	(*game)->assets->t_exit[4] = mlx_load_png("./assets/portal/5.png");
	(*game)->assets->t_exit[5] = mlx_load_png("./assets/portal/6.png");
	(*game)->assets->t_exit[6] = mlx_load_png("./assets/portal/7.png");
	(*game)->assets->t_exit[7] = mlx_load_png("./assets/portal/8.png");
	while (i < 8)
	{
		(*game)->assets->exit[i] = mlx_texture_to_image((*game)->mlx, \
		(*game)->assets->t_exit[i]);
		if (i > 0)
			(*game)->assets->exit[i]->enabled = false;
		i++;
	}
}

void	ft_load_extra(t_game **game)
{
	(*game)->assets->logo = mlx_load_png("./assets/extra/logo.png");
	(*game)->assets->t_forest = mlx_load_png("./assets/extra/forest.png");
	(*game)->assets->forest = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_forest);
	(*game)->assets->t_bgs[0] = mlx_load_png("./assets/extra/bg.png");
	(*game)->assets->bgs[0] = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_bgs[0]);
	(*game)->assets->t_bgs[1] = mlx_load_png("./assets/extra/end_bg.png");
	(*game)->assets->bgs[1] = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_bgs[1]);
	(*game)->assets->t_bgs[2] = mlx_load_png("./assets/extra/bubble.png");
	(*game)->assets->bgs[2] = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_bgs[2]);
	(*game)->assets->t_msg[0] = mlx_load_png("./assets/extra/you_won.png");
	(*game)->assets->msg[0] = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_msg[0]);
	(*game)->assets->t_msg[1] = mlx_load_png("./assets/extra/game_over.png");
	(*game)->assets->msg[1] = mlx_texture_to_image((*game)->mlx, \
						(*game)->assets->t_msg[1]);
}
