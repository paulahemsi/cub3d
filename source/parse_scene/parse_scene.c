/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 01:20:53 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/24 02:08:29 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	check_colors(t_rgb *ceiling, t_rgb *floor)
{
	if (ceiling->red > 255 || ceiling->blue > 255 || ceiling->green > 255)
		return_error(-10);
	if (floor->red > 255 || floor->blue > 255 || floor->green > 255)
		return_error(-10);
}

static void	define_world_size(t_settings *setting, t_map *map)
{
	setting->world[WIDTH] = map->total_column * TILE_SIZE;
	setting->world[HEIGHT] = map->total_row * TILE_SIZE;
}

static void	save_sprites_locations(t_render *game)
{
	char	**map;
	int		row;
	int		col;
	int		i;

	col = 0;
	i = 0;
	map = game->map.row;
	game->sprites = (t_sprite *)malloc(game->num_sprites * sizeof(t_sprite));
	while (map[col])
	{
		row = 0;
		while (map[col][row])
		{
			if (map[col][row] == '2')
			{
				game->sprites[i].pos[X] = row * TILE_SIZE;
				game->sprites[i].pos[Y] = col * TILE_SIZE;
				i++;
			}
			row++;
		}
		col++;
	}
}

void	parse_scene(char *file, t_cub *cub)
{
	char		*line;
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return_error(-2);
	while (get_next_line(fd, &line))
	{
		parse_settings(cub, line);
		free(line);
	}
	parse_settings(cub, line);
	free(line);
	close(fd);
	check_colors(&cub->settings.ceiling, &cub->settings.floor);
	define_world_size(&cub->settings, &cub->game.map);
	fill_map(cub, file, cub->game.map.total_row);
	check_map(&cub->game);
	save_sprites_locations(&cub->game);
	load_textures(cub->settings.path, cub, &cub->game);
}
