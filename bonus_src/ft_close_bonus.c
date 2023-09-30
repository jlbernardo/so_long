/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:35:33 by julberna          #+#    #+#             */
/*   Updated: 2023/09/29 22:41:21 by julberna         ###   ########.fr       */
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
}

void	ft_free_img(t_game **game, mlx_image_t *img[6], mlx_texture_t *t_img[6], int j)
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

void	ft_check_collection(t_game **game, size_t i, size_t j)
{
	int		dino_x;
	int		dino_y;
	int		coin_x;
	int		coin_y;

	dino_x = (*game)->assets->dino[0]->instances->x;
	dino_y = (*game)->assets->dino[0]->instances->y;
	while (i < (*game)->assets->coin[0]->count)
	{
		coin_x = (*game)->assets->coin[0]->instances[i].x;
		coin_y = (*game)->assets->coin[0]->instances[i].y;
		if ((coin_x > dino_x && coin_y > dino_y) && \
		(coin_x < (dino_x + 46) && coin_y < (dino_y + 46)) \
		&& (*game)->assets->coin[0]->instances[i].enabled == true)
		{
			while (++j < 6)
				(*game)->assets->coin[j]->instances[i].enabled = false;
			(*game)->d_collected++;
			if ((*game)->d_collected == (*game)->assets->coin[0]->count)
				(*game)->assets->exit[0]->enabled = true;
		}
		i++;
	}
	ft_check_ending(dino_x, dino_y, game);
}

void	ft_check_ending(int dino_x, int dino_y, t_game **game)
{
	size_t	i;
	int		exit_x;
	int		exit_y;
	int		bat_x;
	int		bat_y;

	i = 0;
	exit_x = (*game)->assets->exit[0]->instances->x;
	exit_y = (*game)->assets->exit[0]->instances->y;
	while (i < (*game)->assets->bat[0]->count)
	{
		bat_x = (*game)->assets->bat[0]->instances[i].x;
		bat_y = (*game)->assets->bat[0]->instances[i].y;
		if ((dino_x > bat_x && dino_y < bat_y) && \
			((dino_x + 45) < (bat_x + 77) && (dino_y + 45) > (bat_y + 37)))
			ft_ending(game, 'l', 5);
		i++;
	}
	if ((dino_x > exit_x && dino_y > exit_y) && \
		(dino_x < (exit_x + 100) && dino_y < (exit_y + 100)) \
		&& (*game)->d_collected == (*game)->assets->coin[0]->count)
		ft_ending(game, 'w', 6);
}

void	ft_ending(t_game **game, char end, int msg_code)
{
	char	*moves;

	(*game)->count->playable = false;
	mlx_image_to_window((*game)->mlx, (*game)->assets->bgs[1], 0, 0);
	if (end == 'w')
	{
		mlx_image_to_window((*game)->mlx, (*game)->assets->msg[0], \
		((*game)->mlx->width / 2) - 110, ((*game)->mlx->height / 2) - 60);
		moves = ft_itoa((*game)->moves);
		ft_printf("\nTotal moves: %s\n", moves);
		free(moves);
	}
	else if (end == 'l')
	{
		mlx_image_to_window((*game)->mlx, (*game)->assets->msg[1], \
		((*game)->mlx->width / 2) - 110, ((*game)->mlx->height / 2) - 60);
	}
	(*game)->assets->str[2] = mlx_put_string((*game)->mlx, \
	"Press ESC to close", ((*game)->mlx->width / 2) - 89, \
	((*game)->mlx->height / 2) + 70);
	ft_message(msg_code);
}
