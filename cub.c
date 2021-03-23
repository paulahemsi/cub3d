/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:03:50 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/23 19:38:14 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void	testando_as_parada_tudo(t_configs *configs)
{
	ft_printf("\n\nPATHS:\n north: %s\n south: %s\n west: %s\n east: %s\n sprite: %s\n\nRGB:\n floor: %i, %i, %i\n ceiling: %i, %i, %i\n\nRESOLUTION:\n width: %u\n height: %u\n\n\n", configs->path.north, configs->path.south, configs->path.west, configs->path.east, configs->path.sprite, configs->floor.red, configs->floor.green, configs->floor.blue, configs->ceiling.red, configs->ceiling.green, configs->ceiling.blue, configs->window_width, configs->window_height);
	int i = 0;
	while (configs->map.row[i] != NULL)
	{
		ft_printf("|%s|\n", configs->map.row[i]);
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

static void	free_paths(t_configs *configs)
{
	free(configs->path.north);
	free(configs->path.south);
	free(configs->path.west);
	free(configs->path.east);
	free(configs->path.sprite);
}

static void	render_cub(char *file)
{
	t_configs	configs;
	char		*line;
	int			fd;

	ft_memset(&configs, 0, sizeof(configs));
	ft_memset(&configs.floor, -1, sizeof(configs.floor));
	ft_memset(&configs.ceiling, -1, sizeof(configs.ceiling));
	if ((fd = open(file, O_RDONLY)) < 0)
		return_error(-2);
	while (get_next_line(fd, &line))
	{
		parse_configs(&configs, line);
		free(line);
	}
	parse_configs(&configs, line);
	free(line);
	close(fd);
	fill_map(&configs, file);
	check_walls(&configs);
	testando_as_parada_tudo(&configs);
	free_paths(&configs);
	free_map(configs.map.row);
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
		//TODO save .bmp
	}
	else
		render_cub(argv[1]);
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
