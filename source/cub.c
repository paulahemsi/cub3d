/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 23:03:50 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/24 01:19:50 by phemsi-a         ###   ########.fr       */
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
