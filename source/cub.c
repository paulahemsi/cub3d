/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:03:50 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 14:23:47 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
	ft_memset(&cub->toggle, -1, sizeof(cub->toggle));
	cub->toggle.bmp_id = 0;
	cub->mlx_ptr = mlx_init();
	if (!(cub->mlx_ptr))
		return_error(cub, -105);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	init_cub(&cub);
	if ((argc == 2) || (argc == 3))
		cub.toggle.save = check_args(&cub, argc, argv);
	else
		return_error(&cub, -101);
	parse_scene(argv[1], &cub);
	render_cub(&cub);
}
