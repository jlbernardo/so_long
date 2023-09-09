/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:26:11 by julberna          #+#    #+#             */
/*   Updated: 2023/09/09 15:03:28 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	main(int32_t argc, const char **argv)
{
	mlx_t	*mlx;
	t_map	**map;

	if (argc != 2)
	{
		ft_printf("%s.\n", mlx_strerror(MLX_INVFILE));
		return (EXIT_FAILURE);
	}
	map = ft_calloc(1, sizeof(t_map *));
	if (ft_check_map_validity((char *)argv[1], map) != 0)
		return (EXIT_FAILURE);
	mlx = ft_open_window(*map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
