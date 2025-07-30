/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:54:17 by dvlachos          #+#    #+#             */
/*   Updated: 2025/07/28 14:54:20 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_err(t_map *map, char *error, int fd)
{
	while (*error)
		write(2, error++, 1);
	write (2, "\n", 1);
	free(map);
	close(fd);
	return (1);
}

void	free_stuff(t_map *map)
{
	int		i;

	i = 0;
	free(map->config->c_path);
	free(map->config->f_path);
	free(map->config->ea_path);
	free(map->config->no_path);
	free(map->config->we_path);
	free(map->config->so_path);
	free(map->config);
	while (map->map[i])
		free(map->map[i++]);
	free(map->map);
	free(map);
}
