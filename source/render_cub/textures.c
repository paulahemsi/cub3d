/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:13:10 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/15 21:30:38 by phemsi-a         ###   ########.fr       */
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

void	load_textures(char **path, t_cub *cub)
{
	t_texture	texture[4];
	int			text;

	text = NORTH;
	while (text <= WEST)
	{
		texture[text].img = mlx_xpm_file_to_image(cub->mlx_ptr, path[text], &texture[text].width, &texture[text].height);
		if (!(texture[text].img))
			return_error(-12);
		text++;
	}
	
	text = NORTH;
	while (text <= WEST)
	{
		free(texture[text].img);
		//mlx_destroy_image(img, texture[text].img);
		//!destruir janela destruir display free mlx
		text++;
	}
}