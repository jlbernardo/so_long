/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_validity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:30:44 by julberna          #+#    #+#             */
/*   Updated: 2023/09/14 14:01:25 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_map_validity(int argc, char *file, t_game **game)
{
	int	i;

	if (argc != 2)
		exit(ft_printf("%s.\n", mlx_strerror(MLX_INVFILE)));
	if (!file)
		exit(ft_printf("%s.\n", mlx_strerror(MLX_INVFILE)));
	i = ft_strlen(file);
	if (ft_strncmp(&file[i - 4], ".ber", 4) != 0)
		exit(ft_printf("%s.\n", mlx_strerror(MLX_INVEXT)));
	(*game) = ft_calloc(1, sizeof(t_game));
	ft_count_lines(file, game);
	(*game)->count = ft_calloc(1, sizeof(t_count));
	(*game)->count->player = 0;
	(*game)->count->exit = 0;
	(*game)->count->collectible = 0;
	ft_create_matrix(file, game);
	if ((ft_validate_boundary(game, 0, 0) != 0) || \
		(*game)->map->x <= 0 || (*game)->map->y <= 0 || \
		(*game)->count->player != 1 || (*game)->count->exit != 1 || \
		(*game)->count->collectible < 1 || (*game)->map->x == (*game)->map->y)
	{
		i = (*game)->map->y - 1;
		while (i >= 0)
		{
			free((*game)->map->map[i]);
			i--;
		}
		free((*game)->map->map);
		free((*game)->map);
		free((*game)->count);
		free((*game));
		exit(ft_printf("%s.\n", mlx_strerror(MLX_INVFILE)));
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
}

void	ft_create_matrix(char *file, t_game **game)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(file, O_RDONLY);
	(*game)->map->map = ft_calloc((*game)->map->y, sizeof(char *));
	while (i < (*game)->map->y)
	{
		(*game)->map->map[i] = get_next_line(fd);
		(*game)->map->map[i][(*game)->map->x] = '\0';
		i++;
	}
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
				(*game)->map->map[(*game)->map->y - 1][x] != '1')
				return (MLX_INVFILE);
			if ((*game)->map->map[y][x] == 'P')
			{
				(*game)->count->player++;
				(*game)->count->p_init_x = x;
				(*game)->count->p_init_y = y;
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
