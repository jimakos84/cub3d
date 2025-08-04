/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:45:07 by dvlachos          #+#    #+#             */
/*   Updated: 2025/07/25 15:51:15 by dvlachos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*c_path;
	char	*f_path;
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	f;
	bool	c;
}	t_config;

typedef struct s_map
{
	char		**map;
	bool		player;
	t_config	*config;
}	t_map;

	//~~~~~~~~MAP VALIDATION~~~~~~~~//

void	file_valid(char *filename);
void	map_parsing(t_map *map, char *filename);
void	map_parsing2(t_map *map, char *filename);
void	config_validation(t_map *map, char *config_line);
void	map_validation2(t_map *map);
void	set_path(char **dest, bool *seen, char *line, t_map *map);

	//~~~~~~~~UTILS~~~~~~~~//

int		print_err(t_map *map, char *error, int fd);
void	free_stuff(t_map *map);
bool	is_empty_line(char *line);
bool	is_config_line(char *line);
bool	is_map_line(char *line);

	//~~~~~~~~INIT~~~~~~~~//

void	init_map(t_map *map);

#endif
