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

bool	is_map_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	while (*line)
	{
		if (*line != ' ' && *line != '0' && *line != '1' &&
			*line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			return (false);
		line++;
	}
	return (true);
}

bool	is_config_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if(	ft_strncmp("NO ", line, 3) == 0 ||
		ft_strncmp("SO ", line, 3) == 0 ||
		ft_strncmp("WE ", line, 3) == 0 ||
		ft_strncmp("EA ", line, 3) == 0 ||
		ft_strncmp("F ", line, 2) == 0 ||
		ft_strncmp("C ", line, 2) == 0)
			return (true);
	else
		return (false);
}

bool	is_empty_line(char *line)
{
	if (*line == '\n')
		return (true);
	while(*line)
	{
		if (*line != ' ' && *line != '\t')
			return (false);
		line++;
	}
	return (true);
}

int	print_err(t_map *map, char *error, int fd)
{
	if (*error)
		ft_putendl_fd(error, 2);
	free_stuff(map);
	if (fd >= 0)
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
