/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:34:13 by julberna          #+#    #+#             */
/*   Updated: 2023/09/30 21:44:55 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_animate_bat(t_game **game);

void	ft_load_sprites(t_game **game)
{
	ft_load_dino(game);
	ft_load_coin(game);
	ft_load_bat(game);
	ft_load_extra(game);
	ft_load_portal(game);
	mlx_set_icon((*game)->mlx, (*game)->assets->logo);
	mlx_image_to_window((*game)->mlx, (*game)->assets->bgs[0], 0, 0);
}

void	ft_animate(t_game **game)
{
	static int	d;
	static int	c;
	static int	p;

	(*game)->assets->dino[d]->enabled = !(*game)->assets->dino[d]->enabled;
	if (d == 3)
		d = -1;
	d++;
	(*game)->assets->dino[d]->enabled = !(*game)->assets->dino[d]->enabled;
	(*game)->assets->coin[c]->enabled = !(*game)->assets->coin[c]->enabled;
	if (c == 5)
		c = -1;
	c++;
	(*game)->assets->coin[c]->enabled = !(*game)->assets->coin[c]->enabled;
	if ((*game)->d_collected == (*game)->assets->coin[0]->count)
	{
		(*game)->assets->exit[p]->enabled = !(*game)->assets->exit[p]->enabled;
		if (p == 7)
			p = -1;
		p++;
		(*game)->assets->exit[p]->enabled = !(*game)->assets->exit[p]->enabled;
	}
	ft_animate_bat(game);
	usleep(70000);
}

void	ft_animate_bat(t_game **game)
{
	int			i;

	i = -1;
	while (++i < 2)
		(*game)->assets->bat[i]->enabled = !(*game)->assets->bat[i]->enabled;
}
