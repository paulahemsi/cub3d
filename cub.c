/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:03:50 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/29 11:23:32 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub.h"

static void	testando_as_parada_tudo(t_configs *cub)
{
	ft_printf("\n\nPATHS:\n north: %s\n south: %s\n west: %s\n east: %s\n sprite: %s\n\nRGB:\n floor: %i, %i, %i\n ceiling: %i, %i, %i\n\nRESOLUTION:\n width: %u\n height: %u\n\nPLAYER\n position: %i x %i\n direction: (%i, %i)\n\n\n", cub->path.north, cub->path.south, cub->path.west, cub->path.east, cub->path.sprite, cub->floor.red, cub->floor.green, cub->floor.blue, cub->ceiling.red, cub->ceiling.green, cub->ceiling.blue, cub->width, cub->height, cub->player_pos[X], cub->player_pos[Y], cub->player_dir[X], cub->player_dir[Y]);
	int i = 0;
	while (cub->map.row[i] != NULL)
	{
		ft_printf("|%s|\n", cub->map.row[i]);
		i++;
	}
}

static void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	free_paths(t_configs *cub)
{
	free(cub->path.north);
	free(cub->path.south);
	free(cub->path.west);
	free(cub->path.east);
	free(cub->path.sprite);
}

static void	parse_scene(char *file)
{
	t_configs	cub;
	char		*line;
	int			fd;

	ft_memset(&cub, 0, sizeof(cub));
	ft_memset(&cub.floor, -1, sizeof(cub.floor));
	ft_memset(&cub.ceiling, -1, sizeof(cub.ceiling));
	if ((fd = open(file, O_RDONLY)) < 0)
		return_error(-2);
	while (get_next_line(fd, &line))
	{
		parse_configs(&cub, line);
		free(line);
	}
	parse_configs(&cub, line);
	free(line);
	close(fd);
	fill_map(&cub, file);
	check_walls(&cub);
	testando_as_parada_tudo(&cub);
	render_cub(&cub);
	free_paths(&cub);
	free_map(cub.map.row);
}

static void	check_args(int argc, char **argv)
{
	unsigned int	i;
	unsigned int	length;
	char			*cub;

	length = ft_strlen(argv[1]);
	i = length;
	cub = ft_strnstr(argv[1], ".cub", length);
	if (!(cub) || cub[0] != argv[1][length - 4])
		return_error(-1);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			return_error(-1);
		ft_putstr("TODO: SAVE PRINT\n");
	}
	else
		parse_scene(argv[1]);
}

int			main(int argc, char **argv)
{
	if ((argc == 2) || (argc == 3))
	{
		check_args(argc, argv);
	}
	else
		return_error(-1);
	return (EXIT_SUCCESS);
}
