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

void	init_map(t_map *map)
{
	t_config	*config;

	config = NULL;
	config = malloc(sizeof(t_config));
	if (!config)
		return ;
	map->config = config;
	config->c = false;
	config->f = false;
	config->ea = false;
	config->no = false;
	config->so = false;
	config->we = false;
	config->c_path = NULL;
	config->ea_path = NULL;
	config->f_path = NULL;
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
}

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
		{
			init_map(map);
			map_parsing(map, argv[1]);
			printf("asset: %s\n", map->config->c_path);
			printf("asset: %s\n", map->config->f_path);
			printf("asset: %s\n", map->config->no_path);
			printf("asset: %s\n", map->config->so_path);
			printf("asset: %s\n", map->config->ea_path);
			printf("asset: %s\n", map->config->we_path);
			free_stuff(map);
		}
		return (0);
	}
	else
	{
		write(2, "Error\n", 6);
		return (1);
	}
}
