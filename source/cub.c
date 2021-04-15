/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:03:50 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/15 02:44:24 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


 static void	testando_as_parada_tudo(t_settings *cub)
 {
 	printf("\n\nPATHS:\n north: %s\n south: %s\n west: %s\n east: %s\n sprite: %s\n\nRGB:\n floor: %i, %i, %i\n ceiling: %i, %i, %i\n\nRESOLUTION:\n screen[WIDTH]: %u\n screen[HEIGHT]: %u\n world[WIDTH]: %u\n world[HEIGHT]: %u\n central point: (%i, %i)\n\nPLAYER\n position: (%i, %i)\n move_dir: %i turn dir: %i\nangle: %f\ndistance to projection plane: %i\n\nRAY:\nstep: %f\nangle: %f\n\n\n", cub->path[NORTH], cub->path[SOUTH], cub->path[WEST], cub->path[EAST], cub->path[SPRITE], cub->floor.red, cub->floor.green, cub->floor.blue, cub->ceiling.red, cub->ceiling.green, cub->ceiling.blue, cub->screen[WIDTH], cub->screen[HEIGHT], cub->world[WIDTH], cub->world[HEIGHT], cub->center[X], cub->center[Y], cub->player.pos[X], cub->player.pos[Y], cub->player.direction[MOVE], cub->player.direction[TURN], cub->player.angle, cub->player.plane_dist, cub->ray.step, cub->ray.angle);
 	int i = 0;
 	int j;
 	while (cub->map.row[i] != NULL)
 	{
 		j = 0;
 		while (cub->map.row[i][j] != '\0')
 		{
 			ft_printf("%c", cub->map.row[i][j]);
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
	//!CONTINUAR A REFATORAR DAQUI:
	fill_map(cub, file, cub->game.map.total_row);
	check_map(cub);
	load_textures(cub->settings.path, cub->img);
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

	if (!(cub.mlx_ptr = mlx_init()))
		return_error(-8);
	init_cub(&cub);
	if ((argc == 2) || (argc == 3))
		cub.toggle.save = check_args(argc, argv);
	else
		return_error(-1);
	parse_scene(argv[1], &cub, &img);
	testando_as_parada_tudo(&cub);
	render_cub(&cub, &img);
	//free_cub(&cub); //?chega aqui em algum momento?
	//return (EXIT_SUCCESS);
}
