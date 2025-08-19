/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eala-lah <eala-lah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:25:30 by eala-lah          #+#    #+#             */
/*   Updated: 2025/08/13 14:00:37 by eala-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config	*mock_config(char *filename)
{
	t_config	*cfg;

	cfg = malloc(sizeof(t_config));
	if (!cfg)
		return (NULL);
	ft_bzero(cfg, sizeof(t_config));
	map_parsing(cfg, filename);
	cfg->door_texture = ft_strdup(DOOR_TEXTURE_PATH);
	cfg->sprite_texture = ft_strdup(SPRITE_TEXTURE_PATH);
	return (cfg);
}
