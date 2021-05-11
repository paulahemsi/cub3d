/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:13:10 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/10 23:47:06 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

static void	load_sprites(t_cub *cub, t_sprite *sprites, int total_sprites)
{
	int	i;

	i = 0;
	while (i < total_sprites)
	{
		sprites[i].texture.img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
				cub->settings.path[SPRITE],
				&sprites[i].texture.width,
				&sprites[i].texture.height);
		if (!(sprites[i].texture.img.ptr))
			return_error(cub, -114);
		sprites[i].texture.img.data = mlx_get_data_addr(
				sprites[i].texture.img.ptr,
				&sprites[i].texture.img.bits_per_pixel,
				&sprites[i].texture.img.line_length,
				&sprites[i].texture.img.endian);
		if (!(sprites[i].texture.img.data))
			return_error(cub, -115);
		i++;
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
			return_error(cub, -112);
		texture[text].img.data = mlx_get_data_addr(texture[text].img.ptr,
				&texture[text].img.bits_per_pixel,
				&texture[text].img.line_length,
				&texture[text].img.endian);
		if (!(texture[text].img.data))
			return_error(cub, -113);
		text++;
	}
	load_sprites(cub, game->sprites, game->num_sprites);
}
