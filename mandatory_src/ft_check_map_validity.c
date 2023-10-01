/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_validity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:30:44 by julberna          #+#    #+#             */
/*   Updated: 2023/09/30 20:37:01 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_map_validity(int argc, char *file, t_game **game)
{
	int	i;

	if (argc != 2)
		exit(ft_message(1));
	if (!file)
		exit(ft_message(2));
	i = ft_strlen(file);
	if (ft_strncmp(&file[i - 4], ".ber", 4) != 0)
		exit(ft_message(3));
	(*game) = ft_calloc(1, sizeof(t_game));
	ft_count_lines(file, game);
	ft_create_matrix(file, game, 1, 0);
	ft_create_matrix(file, game, 2, 0);
	i = ft_validate_boundary(game, 0, 0);
	ft_flood(game, (*game)->count->p_init_x, (*game)->count->p_init_y);
	if (i != 0 || (*game)->map->x <= 0 || (*game)->map->y <= 0 || \
		(*game)->count->player != 1 || (*game)->count->collectible < 1 || \
		(*game)->count->exit != 1 || (*game)->map->x == (*game)->map->y || \
		(*game)->count->collectable != (*game)->count->collectible)
	{
		ft_close(game, 2, -1);
		exit(ft_message(4));
	}
}

void	ft_count_lines(char *file, t_game **game)
{
	int		fd;
	char	*string;

	fd = open(file, O_RDONLY);
	string = get_next_line(fd);
	if (string)
	{
		(*game)->map = ft_calloc(1, sizeof(t_map));
		(*game)->map->x = ft_strlen(string) - 1;
	}
	while (string != NULL)
	{
		(*game)->map->y++;
		free(string);
		string = get_next_line(fd);
	}
	free(string);
	close(fd);
	(*game)->count = ft_calloc(1, sizeof(t_count));
	(*game)->count->player = 0;
	(*game)->count->exit = 0;
	(*game)->count->collectible = 0;
}

void	ft_create_matrix(char *file, t_game **game, int kind, int i)
{
	const int	fd = open(file, O_RDONLY);

	if (kind == 1)
	{
		(*game)->map->map = ft_calloc((*game)->map->y, sizeof(char *));
		while (i < (*game)->map->y)
		{
			(*game)->map->map[i] = get_next_line(fd);
			(*game)->map->map[i][(*game)->map->x] = '\0';
			i++;
		}
	}
	else
	{
		(*game)->map->copy = ft_calloc((*game)->map->y, sizeof(char *));
		while (i < (*game)->map->y)
		{
			(*game)->map->copy[i] = get_next_line(fd);
			(*game)->map->copy[i][(*game)->map->x] = '\0';
			i++;
		}
	}
	get_next_line(fd);
	close(fd);
}

int	ft_validate_boundary(t_game **game, int x, int y)
{
	while (y < (*game)->map->y)
	{
		x = 0;
		while (x < (*game)->map->x)
		{
			if ((*game)->map->map[y][0] != '1' || (*game)->map->map[0][x] != '1'
				|| (*game)->map->map[y][(*game)->map->x - 1] != '1' ||
				(*game)->map->map[(*game)->map->y - 1][x] != '1' || \
				ft_strchr("10CPE", (*game)->map->map[y][x]) == NULL)
				return (MLX_INVFILE);
			if ((*game)->map->map[y][x] == 'P')
			{
				(*game)->count->player++;
				(*game)->count->p_init_y = x;
				(*game)->count->p_init_x = y;
			}
			else if ((*game)->map->map[y][x] == 'E')
				(*game)->count->exit++;
			else if ((*game)->map->map[y][x] == 'C')
				(*game)->count->collectible++;
			x++;
		}
		y++;
	}
	return (MLX_SUCCESS);
}

void	ft_flood(t_game **game, int x, int y)
{
	if (x >= 0 && y >= 0 && y < (*game)->map->x && x < (*game)->map->y)
	{
		if ((*game)->map->copy[x][y] == '1' || (*game)->map->copy[x][y] == 'x' \
		|| (*game)->map->copy[x][y] == 'c' || (*game)->map->copy[x][y] == 'e')
			return ;
		else if ((*game)->map->copy[x][y] == '0')
			(*game)->map->copy[x][y] = 'x';
		else if ((*game)->map->copy[x][y] == 'C')
		{
			(*game)->count->collectable++;
			(*game)->map->copy[x][y] = '0';
		}
		else if ((*game)->map->copy[x][y] == 'E')
		{
			(*game)->count->escapable = true;
			(*game)->map->copy[x][y] = 'e';
		}
		ft_flood(game, x + 1, y);
		ft_flood(game, x - 1, y);
		ft_flood(game, x, y + 1);
		ft_flood(game, x, y - 1);
	}
}
