/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:40:44 by dvlachos          #+#    #+#             */
/*   Updated: 2025/07/25 15:40:09 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc == 2)
	{
		file_valid(argv[1]);
		map = malloc(sizeof(t_map));
		if (!map)
			return (1);
		else
			map_parsing(map, argv[1]);
		return (0);
	}
	else
	{
		write(2, "Error\n", 6);
		return (1);
	}
}
