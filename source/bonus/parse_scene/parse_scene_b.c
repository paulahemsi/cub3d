/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 01:20:53 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/06 19:41:27 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static void	check_colors(t_cub *cub, t_rgb *ceiling, t_rgb *floor)
{
	if (ceiling->red > 255 || ceiling->blue > 255 || ceiling->green > 255)
		return_error(cub, -110);
	if (floor->red > 255 || floor->blue > 255 || floor->green > 255)
		return_error(cub, -110);
}

static void	define_resolution_limits(t_cub *cub)
{
	t_settings	*set;
	t_game	*game;

	set = &cub->settings;
	game = &cub->game;
	set->screen[WIDTH] = 1280;
	set->screen[HEIGHT] = 720;
	set->center[X] = floor(set->screen[WIDTH] / 2);
	set->center[Y] = floor(set->screen[HEIGHT] / 2);
	game->player.plane_dist = floor((set->screen[WIDTH] / 2) / tan(HALF_FOV));
	game->ray.step = FOV / set->screen[WIDTH];
	game->ray.total = set->screen[WIDTH];
}

static void	define_world_size(t_settings *setting, t_map *map)
{
	setting->world[WIDTH] = map->total_column * TILE_SIZE;
	setting->world[HEIGHT] = map->total_row * TILE_SIZE;
}

static void	save_sprites_locations(t_game*game)
{
	char	**map;
	int		row;
	int		col;
	int		i;
	int		id;

	col = 0;
	i = 0;
	map = game->map.row;
	game->sprites = (t_sprite *)malloc(game->num_sprites * sizeof(t_sprite));
	ft_memset(game->sprites, 0, sizeof(*game->sprites));
	while (map[col])
	{
		row = 0;
		while (map[col][row])
		{
			if (map[col][row] >= '2' && map[col][row] <= '9')
			{
				id = map[col][row] - '0';
				game->sprites[i].id = id;
				game->sprites[i].pos[X] = row * TILE_SIZE;
				game->sprites[i].pos[Y] = col * TILE_SIZE;
				game->sprites[i].active = TRUE;
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
		return_error(cub, -104);
	define_resolution_limits(cub);
	while (get_next_line(fd, &line))
	{
		parse_settings(cub, line);
		free(line);
	}
	parse_settings(cub, line);
	free(line);
	close(fd);
	check_colors(cub, &cub->settings.ceiling, &cub->settings.floor);
	define_world_size(&cub->settings, &cub->game.map);
	fill_map(cub, file, cub->game.map.total_row);
	check_map(cub, &cub->game);
	save_sprites_locations(&cub->game);
	load_textures(cub->settings.path, cub, &cub->game);
}
