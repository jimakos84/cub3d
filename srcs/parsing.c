/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:10:39 by dvlachos          #+#    #+#             */
/*   Updated: 2025/08/18 13:10:41 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	map_parsing(t_config *cfg, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		exit(print_err(cfg, "Empty", fd));
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	i += 1;
	cfg->map = malloc(sizeof(char *) * i);
	if (!cfg->map)
		exit(print_err(cfg, "Malloc failed", fd));
	close(fd);
	map_parsing2(cfg, filename);
}

// /*
// This function saves the contents of the file into a 2d array.
// */

void	map_parsing2(t_config *cfg, char *filename)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(filename, O_RDONLY);
	cfg->map[i] = get_next_line(fd);
	while (cfg->map[i] != NULL)
	{
		i++;
		cfg->map[i] = get_next_line(fd);
	}
	cfg->map[i] = NULL;
	close(fd);
	i = 0;
	while (cfg->map[i])
	{
		if (is_config_line(cfg->map[i]))
			config_validation(cfg, cfg->map[i]);
		i++;
	}
	map_validation2(cfg);
}

void	config_validation(t_config *cfg, char *config_line)
{
	while (*config_line == ' ' || *config_line == '\t')
		config_line++;
	if (ft_strncmp("NO ", config_line, 3) == 0)
		set_path(&cfg->north_texture, &cfg->no, config_line, cfg);
	else if (ft_strncmp("WE ", config_line, 3) == 0)
		set_path(&cfg->west_texture, &cfg->we, config_line, cfg);
	else if (ft_strncmp("EA ", config_line, 3) == 0)
		set_path(&cfg->east_texture, &cfg->ea, config_line, cfg);
	else if (ft_strncmp("SO ", config_line, 3) == 0)
		set_path(&cfg->south_texture, &cfg->so, config_line, cfg);
	else if (ft_strncmp("F ", config_line, 2) == 0)
		set_path(&cfg->floor_color, &cfg->f, config_line, cfg);
	else if (ft_strncmp("C ", config_line, 2) == 0)
		set_path(&cfg->ceiling_color, &cfg->c, config_line, cfg);
}

void	map_validation2(t_config *cfg)
{
	int		i;
	int		config_count;
	bool	map_started;

	i = 0;
	config_count = 0;
	map_started = false;
	while (cfg->map[i])
	{
		if (is_empty_line(cfg->map[i]) || cfg->map[i][0] == '\n')
		{
			if (map_started)
				exit(print_err(cfg, "Empty line in the map", -1));
			i++;
			continue ;
		}
		if (is_config_line(cfg->map[i]))
			config_count++;
		else if (is_map_line(cfg->map[i]))
		{
			if (config_count != 6)
				exit(print_err(cfg, "Error: configuration failed", -1));
			map_started = true;
			i++;
			continue ;
		}
		else
			exit(print_err(cfg, "Invalid line before map", -1));
		i++;
	}
	if (!map_started)
		exit(print_err(cfg, "Map not found after configuration", -1));
	map_validation3(cfg);
}

void	map_validation3(t_config *cfg)
{
	int		i;

	i = 0;
	while(is_config_line(cfg->map[i]) || is_empty_line(cfg->map[i]))
		i++;
	validate_player(cfg, i);
}

void	validate_player(t_config *cfg, int	map_start)
{
	int		i;

	cfg->player = false;
	while(cfg->map[map_start])
	{
		i = 0;
		while (cfg->map[map_start][i])
		{
			if (cfg->map[map_start][i] == 'N' || cfg->map[map_start][i] == 'S' ||
				cfg->map[map_start][i] == 'W' || cfg->map[map_start][i] == 'E')
				{
					cfg->player = true;
					break;
				}
			i++;
		}
		if (cfg->player)
			break ;
		map_start++;
	}
	if (!cfg->player)
		exit(print_err(cfg, "Player not found", -1));
	cfg->player_x = i;
	cfg->player_y = map_start;
	cfg->player_dir = cfg->map[map_start][i];
}

void	set_path(char **dest, bool *seen, char *line, t_config *cfg)
{
	if (*seen)
	{
		exit(print_err(cfg, "Error: Duplicate asset", -1));
	}
	*seen = true;
	*dest = ft_strtrim(ft_strchr(line, ' '), " \t\n");
}

int			*color_atoia(const char *color_string)
{
	int		*rgb;
	char	**token;
	int		i;

	i = 0;
	rgb = malloc(sizeof(int) * 3);
	token = ft_split(color_string, ',');
	while (token[i] && i < 3)
	{
		rgb [i] = ft_atoi(token[i]);
		if (rgb[i] < 0) rgb[i] = 0;
		if (rgb[i] > 255) rgb[i] = 255;
		i++;
	}
	i = 0;
	while (token[i])
	{
		free(token[i++]);
	}
	free(token);
	return(rgb);
}

uint32_t	color_converter(int *rgb)
{
	uint32_t	color;

	color = 0xFF000000;
	color |= (rgb[0] << 16);
	color |= (rgb[1] << 8);
	color |= rgb[2];
	return (color);
}

