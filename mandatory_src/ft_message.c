/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:53:45 by julberna          #+#    #+#             */
/*   Updated: 2023/09/27 17:06:29 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_message(int msg_code)
{
	static const char	*message[7] = {
		"Hooray, everything works!",
		"Error!\n\nThe quantity of arguments is incorrect."
		" You should provide one (and only one) argument.\n"
		"For example: \"./so_long valid_map.ber\"",
		"Error!\n\nThere seem to be no file available."
		" Please, provide one (and only one) argument.\n"
		"For example: \"./so_long valid_map.ber\"",
		"Error!\n\nFile has the wrong extension."
		" Make sure to run the program with a file ending in '.ber'.",
		"Error!\n\nThe map provided break the game rules."
		" Revise the map provided and confirm it has:\n"
		"1) One (and only one) player starting position (P);\n"
		"2) At least one collectible (C);\n3) One (and only one) exit (E);\n"
		"4) Closed outside walls (map surrounded by 1's);\n"
		"5) Rectangular format - it can't be a square, sorry;\n"
		"6) A valid path, so the player can access everything;\n"
		"7) Only acceptable chars: '10PCE'.",
		"Error!\n\nThe opening of the MLX window failed."
		" Try running the program again.", "\nYAY, YOU WON! ※\\(^o^)/※\n"
		"Wanna try again with a different map? Run the program one more time!\n",
	};

	ft_printf("%s\n", message[msg_code]);
	return (msg_code);
}
