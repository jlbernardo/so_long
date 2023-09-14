/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:26:11 by julberna          #+#    #+#             */
/*   Updated: 2023/09/13 19:32:23 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, const char **argv)
{
	t_game	*game;

	ft_check_map_validity(argc, (char *)argv[1], &game);
	ft_open_window(&game);
	ft_mechanics(&game);
	return (EXIT_SUCCESS);
}
