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

void	file_valid(char *filename, char *ext1, char *ext2)
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
	if (len < 5 || ft_strncmp(filename + len - 4, ext1, 4)
		|| !ft_strncmp(filename + len - 5, ext2, 5))
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
		if (is_config_line(map->map[i]))
			config_validation(map, map->map[i]);
		i++;
	}
	map_validation2(map);
}

void	config_validation(t_map *map, char *config_line)
{
	while (*config_line == ' ' || *config_line == '\t')
		config_line++;
	if (ft_strncmp("NO ", config_line, 3) == 0)
		set_path(&map->config->no_path, &map->config->no, config_line, map);
	else if (ft_strncmp("WE ", config_line, 3) == 0)
		set_path(&map->config->we_path, &map->config->we, config_line, map);
	else if (ft_strncmp("EA ", config_line, 3) == 0)
		set_path(&map->config->ea_path, &map->config->ea, config_line, map);
	else if (ft_strncmp("SO ", config_line, 3) == 0)
		set_path(&map->config->so_path, &map->config->so, config_line, map);
	else if (ft_strncmp("F ", config_line, 2) == 0)
		set_path(&map->config->f_path, &map->config->f, config_line, map);
	else if (ft_strncmp("C ", config_line, 2) == 0)
		set_path(&map->config->c_path, &map->config->c, config_line, map);
}

void	map_validation2(t_map *map)
{
	int		i;
	int		config_count;
	bool	map_started;

	i = 0;
	config_count = 0;
	map_started = false;
	while (map->map[i])
	{
		if (is_empty_line(map->map[i]) || map->map[i][0] == '\n')
		{
			if (map_started)
				exit(print_err(map, "Empty line in the map", -1));
			i++;
			continue ;
		}
		if (is_config_line(map->map[i]))
			config_count++;
		else if (is_map_line(map->map[i]))
		{
			if (config_count != 6)
				exit(print_err(map, "Error: configuration failed", -1));
			map_started = true;
			i++;
			continue ;
		}
		else
			exit(print_err(map, "Invalid line before map", -1));
		i++;
	}
	if (!map_started)
		exit(print_err(map, "Map not found after configuration", -1));
	map_validation3(map);
}

void	map_validation3(t_map *map)
{
	int		i;

	i = 0;
	while(is_config_line(map->map[i]) || is_empty_line(map->map[i]))
		i++;
	validate_player(map, i);
}

void	validate_player(t_map *map, int	map_start)
{
	int		i;

	map->player = false;
	while(map->map[map_start])
	{
		i = 0;
		while (map->map[map_start][i])
		{
			if (map->map[map_start][i] == 'N' || map->map[map_start][i] == 'S' ||
				map->map[map_start][i] == 'W' || map->map[map_start][i] == 'E')
				{
					map->player = true;
					break;
				}
			i++;
		}
		if (map->player)
			break ;
		map_start++;
	}
	if (!map->player)
		exit(print_err(map, "Player not found", -1));
	map->player_x = i;
	map->player_y = map_start;
	map->player_dir = map->map[map_start][i];
	printf("Player %c x/y: %d %d\n", map->player_dir, i, map_start);
}

void	set_path(char **dest, bool *seen, char *line, t_map *map)
{
	if (*seen)
	{
		exit(print_err(map, "Error: Duplicate asset", -1));
	}
	*seen = true;
	*dest = ft_strtrim(ft_strchr(line, ' '), " \t\n");
}
