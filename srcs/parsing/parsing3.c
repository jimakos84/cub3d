/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:01:49 by dvlachos          #+#    #+#             */
/*   Updated: 2025/08/29 17:01:51 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D');
}

static int is_cell_enclosed(char **map, size_t i, size_t j)
{
	if (i == 0 || j >= ft_strlen(map[i - 1]) || map[i - 1][j] == ' ')
		return (0);
	if (!map[i + 1] || j >= ft_strlen(map[i + 1]) || map[i + 1][j] == ' ')
		return (0);
	if (j == 0 || map[i][j - 1] == ' ')
		return (0);
	if (map[i][j + 1] == '\0' || map[i][j + 1] == ' ')
		return (0);
	return (1);
}	

static int	map_is_enclosed2(int first_map_line, char **map, t_config *cfg)
{
	int		i;
	int		j;

	i = first_map_line;
	j = 0;
	while (map[i][j])
	{
		if (is_walkable(map[i][j]))
			return (print_err(cfg, "Map is not enclosed (top line)", -1));
		j++;
	}
	while (map[i + 1])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_walkable(map[i][j]))
			{
				if (!is_cell_enclosed(map, i, j))
					return (print_err(cfg, "Map is not enclosed (middle)", -1));
			}
			j++;
		}
		i++;
	}
	j = 0;
	while (map[i][j])
	{
		if (is_walkable(map[i][j]))
			return (print_err(cfg, "Map is not enclosed (bottom line)", -1));
		j++;
	}
	return (1);
}

static int	map_is_enclosed(t_config *cfg)
{
	int		i;
	int		first_map_line;

	i = 0;
	first_map_line = 0;
	while (cfg->map[i])
	{
		if (is_map_line(cfg->map[i]))
		{
			first_map_line = i;
			break ;
		}
		i++;
	}
	if (!map_is_enclosed2(first_map_line, cfg->map, cfg))
		return (0);
	return (1);
}

static int	read_map_lines(t_config *cfg, char *filename)
{
	int		fd;
	int		i;
	int		max_len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	max_len = 0;
	cfg->map[i] = get_next_line(fd);
	while (cfg->map[i] != NULL)
	{
		if ((int)ft_strlen(cfg->map[i]) > max_len)
			max_len = ft_strlen(cfg->map[i]);
		cfg->map[++i] = get_next_line(fd);
	}
	cfg->map[i] = NULL;
	close(fd);
	return (max_len);
}

static bool	pad_map_lines(t_config *cfg, int max_len)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (cfg->map[i])
	{
		if ((int)ft_strlen(cfg->map[i]) < max_len)
		{
			new_line = malloc(max_len + 1);
			if (!new_line)
				return (print_err(cfg, "Malloc failed", -1));
			j = -1;
			while (cfg->map[i][++j])
				new_line[j] = cfg->map[i][j];
			while (j < max_len)
				new_line[j++] = ' ';
			new_line[j] = '\0';
			free(cfg->map[i]);
			cfg->map[i] = new_line;
		}
		i++;
		if (!map_is_enclosed(cfg))
			return (false);
	}
	return (true);
}

static void	process_config_lines(t_config *cfg)
{
	int	i;

	i = 0;
	while (cfg->map[i])
	{
		if (is_config_line(cfg->map[i]))
			config_validation(cfg, cfg->map[i]);
		i++;
	}
}

bool	map_parsing2(t_config *cfg, char *filename)
{
	int	max_len;

	max_len = read_map_lines(cfg, filename);
	if (max_len < 0)
		return (print_err(cfg, NULL, -1));
	if (!pad_map_lines(cfg, max_len))
		return (false);
	process_config_lines(cfg);
	if (!map_validation2(cfg))
		return (false);
	return (true);
}
