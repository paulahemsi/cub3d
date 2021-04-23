/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:03:50 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/23 21:01:35 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


 static void	testando_as_parada_tudo(t_cub *cub)
 {
 	printf("\n\nRGB:\n floor: %i, %i, %i\n ceiling: %i, %i, %i\n\nRESOLUTION:\n screen[WIDTH]: %u\n screen[HEIGHT]: %u\n world[WIDTH]: %u\n world[HEIGHT]: %u\n central point: (%i, %i)\n\nPLAYER\n position: (%i, %i)\n move_dir: %i turn dir: %i\nangle: %f\ndistance to projection plane: %i\n\nRAY:\nstep: %f\nangle: %f\nSPRITES:\nnum: %i\n\n\n", cub->settings.floor.red, cub->settings.floor.green, cub->settings.floor.blue, cub->settings.ceiling.red, cub->settings.ceiling.green, cub->settings.ceiling.blue, cub->settings.screen[WIDTH], cub->settings.screen[HEIGHT], cub->settings.world[WIDTH], cub->settings.world[HEIGHT], cub->settings.center[X], cub->settings.center[Y], cub->game.player.pos[X], cub->game.player.pos[Y], cub->game.player.direction[MOVE], cub->game.player.direction[TURN], cub->game.player.angle, cub->game.player.plane_dist, cub->game.ray.step, cub->game.ray.angle, cub->game.num_sprites);
 	int i = 0;
 	int j;
 	while (cub->game.map.row[i] != NULL)
 	{
 		j = 0;
 		while (cub->game.map.row[i][j] != '\0')
 		{
 			ft_printf("%c", cub->game.map.row[i][j]);
 			j++;
 		}
 		ft_printf("\n");
 		i++;
 	}
 }


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

static void	parse_scene(char *file, t_cub *cub)
{
	char		*line;
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return_error(-2);
	while (get_next_line(fd, &line))
	{
		parse_configs(cub, line);
		free(line);
	}
	parse_configs(cub, line);
	free(line);
	close(fd);
	check_colors(&cub->settings.ceiling, &cub->settings.floor);
	define_world_size(&cub->settings, &cub->game.map);
	fill_map(cub, file, cub->game.map.total_row);
	check_map(&cub->game);
	save_sprites_locations(&cub->game);
	load_textures(cub->settings.path, cub, &cub->game);
}

static int	check_args(int argc, char **argv)
{
	unsigned int	length;
	char			*extension;

	length = ft_strlen(argv[1]);
	extension = ft_strnstr(argv[1], ".cub", length);
	if (!(extension) || extension[0] != argv[1][length - 4])
		return_error(-1);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			return_error(-1);
		else
			return (TRUE);
	}
	return (FALSE);
}

int			main(int argc, char **argv)
{
	t_cub	cub;

	init_cub(&cub);
	if ((argc == 2) || (argc == 3))
		cub.toggle.save = check_args(argc, argv);
	else
		return_error(-1);
	parse_scene(argv[1], &cub);
	testando_as_parada_tudo(&cub);
	render_cub(&cub);
	//free_cub(&cub); //?chega aqui em algum momento?
	//return (EXIT_SUCCESS);
}
