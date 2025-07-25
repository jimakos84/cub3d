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

typedef struct s_map
{
	char	**map;
}	t_map;

	//~~~~~~~~MAP VALIDATION~~~~~~~~//

void	file_valid(char *filename);
void	map_parsing(t_map *map, char *filename);
void	map_parsing2(t_map *map, char *filename);
int		print_err(t_map *map, char *error, int fd);

#endif
