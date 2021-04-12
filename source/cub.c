/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:03:50 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/12 17:05:11 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** static void	testando_as_parada_tudo(t_configs *cub)
** {
** 	printf("\n\nPATHS:\n north: %s\n south: %s\n west: %s\n east: %s\n sprite: %s\n\nRGB:\n floor: %i, %i, %i\n ceiling: %i, %i, %i\n\nRESOLUTION:\n screen_width: %u\n screen_height: %u\n world_width: %u\n world_height: %u\n central point: (%i, %i)\n\nPLAYER\n position: (%i, %i)\n move_dir: %i turn dir: %i\nangle: %f\ndistance to projection plane: %i\n\nRAY:\nstep: %f\nangle: %f\n\n\n", cub->path.north, cub->path.south, cub->path.west, cub->path.east, cub->path.sprite, cub->floor.red, cub->floor.green, cub->floor.blue, cub->ceiling.red, cub->ceiling.green, cub->ceiling.blue, cub->screen_width, cub->screen_height, cub->world_width, cub->world_height, cub->center[X], cub->center[Y], cub->player.pos[X], cub->player.pos[Y], cub->player.move_dir, cub->player.turn_dir, cub->player.angle, cub->player.plane_dist, cub->ray.step, cub->ray.angle);
** 	int i = 0;
** 	int j;
** 	while (cub->map.row[i] != NULL)
** 	{
** 		j = 0;
** 		while (cub->map.row[i][j] != '\0')
** 		{
** 			ft_printf("%c", cub->map.row[i][j]);
** 			j++;
** 		}
** 		ft_printf("\n");
** 		i++;
** 	}
** }
** 
*/

static void	check_colors(t_rgb *ceiling, t_rgb *floor)
{
	if (ceiling->red > 255 || ceiling->blue > 255 || ceiling->green > 255)
		return_error(-10);
	if (floor->red > 255 || floor->blue > 255 || floor->green > 255)
		return_error(-10);
}

static void	parse_scene(char *file, t_configs *cub)
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
	check_colors(&cub->ceiling, &cub->floor);
	fill_map(cub, file, cub->map.total_row);
	check_map(cub);
}

static void	check_args(int argc, char **argv)
{
	unsigned int	length;
	char			*cub;

	length = ft_strlen(argv[1]);
	cub = ft_strnstr(argv[1], ".cub", length);
	if (!(cub) || cub[0] != argv[1][length - 4])
		return_error(-1);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			return_error(-1);
		ft_putstr("TODO: SAVE PRINT\n");
	}
}

int			main(int argc, char **argv)
{
	t_configs	cub;

	init_cub(&cub);
	if ((argc == 2) || (argc == 3))
		check_args(argc, argv);
	else
		return_error(-1);
	parse_scene(argv[1], &cub);
	render_cub(&cub);
	free_cub(&cub); //?chega aqui em algum momento?
	return (EXIT_SUCCESS);
}
