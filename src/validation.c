/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:59:34 by dvlachos          #+#    #+#             */
/*   Updated: 2025/07/25 15:49:19 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
This functions ensures that the map file exists and permissions allow us to
open it. Secondly it checks whether the extension is the correct one.
*/

void	file_valid(char *filename)
{
	int		len;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Invalid file\n", 2);
		exit (1);
	}
	else
		close(fd);
	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4)
		|| !ft_strncmp(filename + len - 5, "/.cub", 5))
	{
		ft_putstr_fd("Invalid file!\n", 2);
		exit(1);
	}
}
/*
A function that checks if the file is empty and secondly it counts
the amounts of lines in the file, in order to allocate the correct 
amount of memory.
*/

void	map_parsing(t_map *map, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		exit(print_err(map, "Empty", fd));
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	i += 1;
	map->map = malloc(sizeof(char *) * i);
	if (!map->map)
		exit(print_err(map, "Malloc failed", fd));
	close(fd);
	map_parsing2(map, filename);
}

/*
This function saves the contents of the file into a 2d array.
*/

void	map_parsing2(t_map *map, char *filename)
{
	int		i;
	int		fd;
	char	*temp;

	i = 0;
	fd = open(filename, O_RDONLY);
	map->map[i] = get_next_line(fd);
	while (map->map[i] != NULL)
	{
		i++;
		map->map[i] = get_next_line(fd);
	}
	map->map[i] = NULL;
	close(fd);
	i = 0;
	while (map->map[i])
	{
		temp = map->map[i];
		map->map[i] = ft_strtrim(temp, " \t");
		free(temp);
		i++;
	}
	map_validation(map);
}

void	map_validation(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map->map[j])
	{
		if (ft_strncmp("NO ", map->map[j], 3) == 0)
			set_path(&map->config->no_path, &map->config->no, map->map[j], map);
		else if (ft_strncmp("WE ", map->map[j], 3) == 0)
			set_path(&map->config->we_path, &map->config->we, map->map[j], map);
		else if (ft_strncmp("EA ", map->map[j], 3) == 0)
			set_path(&map->config->ea_path, &map->config->ea, map->map[j], map);
		else if (ft_strncmp("SO ", map->map[j], 3) == 0)
			set_path(&map->config->so_path, &map->config->so, map->map[j], map);
		else if (ft_strncmp("F ", map->map[j], 2) == 0)
			set_path(&map->config->f_path, &map->config->f, map->map[j], map);
		else if (ft_strncmp("C ", map->map[j], 2) == 0)
			set_path(&map->config->c_path, &map->config->c, map->map[j], map);
		j++;
	}
}

// bool	assets_found(t_map *map)
// {
// 	if (map->config->c && map->config->ea && map->config->f
// 			&& map->config->no && map->config->so && map->config->we)
// 			return (true);
// 	else
// 		return (false);
// }

void	set_path(char **dest, bool *seen, char *line, t_map *map)
{
	if (*seen)
	{
		ft_putendl_fd("Duplicate asset!", 2);
		free_stuff(map);
		exit(1);
	}
	*seen = true;
	*dest = ft_strtrim(ft_strchr(line, ' '), " \t\n");
}
