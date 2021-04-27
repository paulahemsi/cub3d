/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:13:10 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/27 02:05:57 by phemsi-a         ###   ########.fr       */
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
	game->hud.img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/hud.XPM",
			&game->hud.width, &game->hud.height);
	game->hud.img.data = mlx_get_data_addr(game->hud.img.ptr,
			&game->hud.img.bits_per_pixel,
			&game->hud.img.line_length,
			&game->hud.img.endian);
}

static void	load_skybox(t_cub *cub, t_render *game)
{
	game->skybox.img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/skybox.xpm",
			&game->skybox.width, &game->skybox.height);
	game->skybox.img.data = mlx_get_data_addr(game->skybox.img.ptr,
			&game->skybox.img.bits_per_pixel,
			&game->skybox.img.line_length,
			&game->skybox.img.endian);
}

static void	load_sprites(t_cub *cub, t_sprite *sprites, int total_sprites)
{
	int	i;

	i = 0;
	while (total_sprites > 0)
	{
		sprites[i].texture.img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
				cub->settings.path[SPRITE],
				&sprites[i].texture.width,
				&sprites[i].texture.height);
		if (!(sprites[i].texture.img.ptr))
			return_error(-12);
		sprites[i].texture.img.data = mlx_get_data_addr(
				sprites[i].texture.img.ptr,
				&sprites[i].texture.img.bits_per_pixel,
				&sprites[i].texture.img.line_length,
				&sprites[i].texture.img.endian);
		if (!(sprites[i].texture.img.data))
			return_error(-12);
		i++;
		total_sprites--;
	}
}

void	load_textures(char **path, t_cub *cub, t_render *game)
{
	t_texture	*texture;
	int			text;

	game->texture = (t_texture *)malloc(4 * sizeof(t_texture));
	texture = game->texture;
	text = NORTH;
	while (text <= WEST)
	{
		texture[text].img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr, path[text],
				&texture[text].width, &texture[text].height);
		if (!(texture[text].img.ptr))
			return_error(-12);
		texture[text].img.data = mlx_get_data_addr(texture[text].img.ptr,
				&texture[text].img.bits_per_pixel,
				&texture[text].img.line_length,
				&texture[text].img.endian);
		if (!(texture[text].img.data))
			return_error(-12);
		text++;
	}
	load_hud(cub, game);
	load_sprites(cub, game->sprites, game->num_sprites);
	load_skybox(cub, game);
	free_paths(cub->settings.path);
}
