/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:13:10 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/22 20:39:40 by phemsi-a         ###   ########.fr       */
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

static void	load_hud(t_cub *cub, t_render *game)
{
	game->hearts.img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/pixel_heart_edit.XPM", &game->hearts.width, &game->hearts.height);
	game->hearts.img.data = mlx_get_data_addr(game->hearts.img.ptr, &game->hearts.img.bits_per_pixel, &game->hearts.img.line_length, &game->hearts.img.endian); 
}

static void	load_skybox(t_cub *cub, t_render *game)
{
	game->skybox.img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/skybox.xpm", &game->skybox.width, &game->skybox.height);
	game->skybox.img.data = mlx_get_data_addr(game->skybox.img.ptr, &game->skybox.img.bits_per_pixel, &game->skybox.img.line_length, &game->skybox.img.endian); 
}

static void	load_sprites(t_cub *cub, t_render *game)
{
	int i;
	int total_sprites;
	i = 0;
	
	total_sprites = game->num_sprites;
	while (total_sprites > 0)
	{
		game->sprites[i].texture.img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr, cub->settings.path[SPRITE], &game->sprites[i].texture.width, &game->sprites[i].texture.height);
		if (!(game->sprites[i].texture.img.ptr))
			return_error(-12);
		game->sprites[i].texture.img.data = mlx_get_data_addr(game->sprites[i].texture.img.ptr, &game->sprites[i].texture.img.bits_per_pixel, &game->sprites[i].texture.img.line_length, &game->sprites[i].texture.img.endian);
		if (!(game->sprites[i].texture.img.data))
			return_error(-12);
		i++;
		total_sprites--;
	}
}

void	load_textures(char **path, t_cub *cub, t_render *game)
{
	int			text;

	game->texture = (t_texture *)malloc(4 * sizeof(t_texture));
	text = NORTH;
	while (text <= WEST)
	{
		game->texture[text].img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr, path[text], &game->texture[text].width, &game->texture[text].height);
		if (!(game->texture[text].img.ptr))
			return_error(-12);
		game->texture[text].img.data = mlx_get_data_addr(game->texture[text].img.ptr, &game->texture[text].img.bits_per_pixel, &game->texture[text].img.line_length, &game->texture[text].img.endian);
		if (!(game->texture[text].img.data))
			return_error(-12);
		text++;
	}
	load_hud(cub, game);
	load_sprites(cub, game);
	load_skybox(cub, game);
	free_paths(cub->settings.path);
}