/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:03:50 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/20 01:29:17 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void	render_cub(int scene_fd)
{
	t_configs	configs;
	char		*line;

	ft_memset(&configs, 0, sizeof(configs));
	ft_memset(&configs.floor, -1, sizeof(configs.floor));
	ft_memset(&configs.ceiling, -1, sizeof(configs.ceiling));
	while (get_next_line(scene_fd, &line))
	{
		parse_configs(&configs, line);
		free(line);
	}
	//TODO free all config struct function
	free(configs.path.north);
	free(configs.path.south);
	free(configs.path.west);
	free(configs.path.east);
	free(configs.path.sprite);
	free(line);
}

static void	check_args(int argc, char **argv)
{
	unsigned int	i;
	unsigned int	length;
	char			*cub;
	int				fd;

	length = ft_strlen(argv[1]);
	i = length;
	cub = ft_strnstr(argv[1], ".cub", length);
	if (!(cub) || cub[0] != argv[1][length - 4])
		return_error(-1);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return_error(-2);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			return_error(-1);
		ft_putstr("TODO: SAVE PRINT\n");
		//TODO save .bmp
	}
	else
		render_cub(fd);
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
