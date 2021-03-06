/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:03:50 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/13 23:04:06 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/cub.h"

static int	check_args(t_cub *cub, int argc, char **argv)
{
	unsigned int	length;
	char			*extension;

	length = ft_strlen(argv[1]);
	extension = ft_strnstr(argv[1], ".cub", length);
	if (!(extension) || extension[0] != argv[1][length - 4])
		return_error(cub, -102);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			return_error(cub, -103);
		else
			return (TRUE);
	}
	return (FALSE);
}

static void	init_cub(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(*cub));
	ft_memset(&cub->settings.floor, -1, sizeof(cub->settings.floor));
	ft_memset(&cub->settings.ceiling, -1, sizeof(cub->settings.ceiling));
	cub->mlx_ptr = mlx_init();
	cub->game.texture = NULL;
	cub->game.sprites = NULL;
	if (!(cub->mlx_ptr))
		return_error(cub, -105);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	init_cub(&cub);
	if ((argc == 2) || (argc == 3))
		cub.save = check_args(&cub, argc, argv);
	else
		return_error(&cub, -101);
	parse_scene(argv[1], &cub);
	render_cub(&cub);
	return (0);
}
