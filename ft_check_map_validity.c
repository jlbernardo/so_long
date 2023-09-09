/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_validity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:30:44 by julberna          #+#    #+#             */
/*   Updated: 2023/09/09 13:53:51 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	ft_check_map_validity(char *file, t_map **map)
{
	t_map		*temp_map;
	int32_t		len;
	t_essential	item;

	if (!file)
		return (ft_printf("%s.\n", mlx_strerror(MLX_INVFILE)));
	len = ft_strlen(file);
	if (ft_strncmp(&file[len - 4], ".ber", 4) != 0)
		return (ft_printf("%s.\n", mlx_strerror(MLX_INVEXT)));
	temp_map = ft_create_matrix(open(file, O_RDONLY));
	item.player = 0;
	item.exit = 0;
	item.collectible = 0;
	if (ft_check_boundary(temp_map, item, 0, 0) != 0)
		return (ft_printf("%s.\n", mlx_strerror(MLX_INVFILE)));
	if (temp_map->x <= 0 || temp_map->y <= 0)
	{
		mlx_strerror(MLX_INVDIM);
		exit(MLX_INVDIM);
	}
	*map = temp_map;
	return (MLX_SUCCESS);
}

t_map	*ft_create_matrix(int fd)
{
	char			*string;
	char			*free_ptr;
	t_map			*map;

	string = get_next_line(fd);
	map = ft_calloc(1, sizeof(t_map));
	map->inline_map = ft_calloc(1, sizeof(char));
	while (string != NULL)
	{
		free_ptr = map->inline_map;
		map->inline_map = ft_strjoin(map->inline_map, string);
		free(free_ptr);
		free_ptr = string;
		string = get_next_line(fd);
		free(free_ptr);
	}
	map->map = ft_split(map->inline_map, '\n');
	map->x = ft_strlen(map->map[0]);
	map->y = ft_count_lines(map->inline_map);
	free(string);
	return (map);
}

int32_t	ft_check_boundary(t_map *map, t_essential item, int x, int y)
{
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (map->map[0][x] != '1' ||
				map->map[y][0] != '1' ||
				map->map[y][map->x - 1] != '1' ||
				map->map[map->y - 1][x] != '1')
				return (MLX_INVFILE);
			if (map->map[y][x] == 'P')
				item.player++;
			else if (map->map[y][x] == 'E')
				item.exit++;
			else if (map->map[y][x] == 'C')
				item.collectible++;
			x++;
		}
		y++;
	}
	if (item.player != 1 || item.exit != 1 || \
		item.collectible < 1 || map->x == map->y)
		return (MLX_INVFILE);
	return (MLX_SUCCESS);
}

int32_t	ft_count_lines(char *map)
{
	int32_t	lines;
	int32_t	i;

	i = 0;
	lines = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
			lines++;
		i++;
	}
	return (lines);
}
