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
}

int	print_err(t_map *map, char *error, int fd)
{
	while (*error)
		write(2, error++, 1);
	write (2, "\n", 1);
	free(map);
	close(fd);
	return (1);
}
