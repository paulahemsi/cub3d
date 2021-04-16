/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:13:10 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/16 21:49:09 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts a xpm file to a new image instance.
**
** @param  void *mlx_ptr   the mlx instance;
** @param  char *filename  the file to load;
** @param  int  *width     a pointer to where the width ought to be written;
** @param  int  *height    a pointer to where the height ought to be written;
** @return void *          the image instance.
*/

#include "../../includes/cub.h"

void	load_textures(char **path, t_cub *cub, t_render *game)
{
	int			text;

	game->texture = (t_texture *)malloc(4 * sizeof(t_texture));
	text = NORTH;
	while (text <= WEST)
	{
		game->texture[text].img = mlx_xpm_file_to_image(cub->mlx_ptr, path[text], &game->texture[text].width, &game->texture[text].height);
		if (!(game->texture[text].img))
			return_error(-12);
		game->texture[text].img->data = mlx_get_data_addr(game->texture[text].img, &game->texture[text].img->bits_per_pixel, &game->texture[text].img->line_length, &game->texture[text].img->endian);
		if (!(game->texture[text].img->data))
			return_error(-12);
		text++;
	}
	free_paths(cub->settings.path);
}