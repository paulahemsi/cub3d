/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 01:20:53 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/13 23:36:51 by phemsi-a         ###   ########.fr       */
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
	t_game		*game;

	set = &cub->settings;
	game = &cub->game;
	set->screen[WIDTH] = 1280;
	set->screen[HEIGHT] = 720;
	set->center[X] = floor(set->screen[WIDTH] / 2);
	set->center[Y] = floor(set->screen[HEIGHT] / 2);
	game->player.plane_dist = floor((set->screen[WIDTH] / 2) / tan(HALF_FOV));
	game->ray.step = FOV / set->screen[WIDTH];
	game->ray.total = set->screen[WIDTH];
	set->world[WIDTH] = game->map.total_column * TILE_SIZE;
	set->world[HEIGHT] = game->map.total_row * TILE_SIZE;
}

static void	set_sprite(t_game *game, int i, int col, int row)
{
	int	id;

	id = game->map.row[col][row] - '0';
	game->sprites[i].id = id;
	game->sprites[i].pos[X] = row * TILE_SIZE;
	game->sprites[i].pos[Y] = col * TILE_SIZE;
	game->sprites[i].active = TRUE;
}

static void	save_sprites_locations(t_game*game)
{
	char	**map;
	int		row;
	int		col;
	int		i;

	col = 0;
	i = 0;
	map = game->map.row;
	game->sprites = (t_sprite *)ft_calloc(game->num_sprites, sizeof(t_sprite));
	while (map[col])
	{
		row = 0;
		while (map[col][row])
		{
			if (map[col][row] >= '2' && map[col][row] <= '9')
			{
				set_sprite(game, i, col, row);
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
	while (get_next_line(fd, &cub->settings.line))
	{
		line = cub->settings.line;
		parse_settings(cub, line);
		ft_free_and_null((void **)&cub->settings.line);
	}
	line = cub->settings.line;
	parse_settings(cub, line);
	ft_free_and_null((void **)&cub->settings.line);
	close(fd);
	check_colors(cub, &cub->settings.ceiling, &cub->settings.floor);
	fill_map(cub, file, cub->game.map.total_row);
	check_map(cub, &cub->game);
	define_resolution_limits(cub);
	save_sprites_locations(&cub->game);
	load_textures(cub->settings.path, cub, &cub->game);
}
