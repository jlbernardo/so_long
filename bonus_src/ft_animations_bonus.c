/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:34:13 by julberna          #+#    #+#             */
/*   Updated: 2023/09/29 16:24:25 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_animate(t_game **game)
{
	int			i;
	static int	anim_d;
	static int	anim_c;

	(*game)->assets->dino[anim_d]->enabled = !(*game)->assets->dino[anim_d]->enabled;
	if (anim_d == 3)
		anim_d = -1;
	anim_d++;
	(*game)->assets->dino[anim_d]->enabled = !(*game)->assets->dino[anim_d]->enabled;
	(*game)->assets->coin[anim_c]->enabled = \
	!(*game)->assets->coin[anim_c]->enabled;
	if (anim_c == 5)
		anim_c = -1;
	anim_c++;
	(*game)->assets->coin[anim_c]->enabled = \
	!(*game)->assets->coin[anim_c]->enabled;
	i = 0;
	while (i < 2)
	{
		(*game)->assets->bat[i]->enabled = !(*game)->assets->bat[i]->enabled;
		i++;
	}
	usleep(120000);
}
