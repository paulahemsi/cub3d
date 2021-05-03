/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:13:10 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/03 15:14:54 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static char	*define_hud_name(int id)
{
	char	*name;
	char	*aux;

	name = ft_itoa(id);
	aux = ft_strjoin("./textures/hud_", name);
	free(name);
	name = ft_strjoin(aux, ".XPM");
	free(aux);
	return (name);
}

static void	load_hud(t_cub *cub, t_game *game)
{
	int id;
	char *name;

	id = 0;
	while (id <= 5)
	{
		name = define_hud_name(id);
		game->hud[id].img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr, name,
				&game->hud[id].width, &game->hud[id].height);
		game->hud[id].img.data = mlx_get_data_addr(game->hud[id].img.ptr,
				&game->hud[id].img.bits_per_pixel,
				&game->hud[id].img.line_length,
				&game->hud[id].img.endian);
		id++;
		free (name);
	}
}

// static void	load_skybox(t_cub *cub, t_game *game)
// {
// 	game->skybox.img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
// 			"./textures/skybox.xpm",
// 			&game->skybox.width, &game->skybox.height);
// 	game->skybox.img.data = mlx_get_data_addr(game->skybox.img.ptr,
// 			&game->skybox.img.bits_per_pixel,
// 			&game->skybox.img.line_length,
// 			&game->skybox.img.endian);
// }

static char	*define_sprite_name(t_sprite *sprite)
{
	char	*name;
	char	*aux;
	int		id;

	id = sprite->id;
	name = ft_itoa(id);
	aux = ft_strjoin("./textures/sprite", name);
	free(name);
	name = ft_strjoin(aux, ".XPM");
	free(aux);
	return (name);
}

static void	load_sprites(t_cub *cub, t_sprite *sprites, int total_sprites)
{
	int		i;
	char	*name;

	i = 0;
	while (i < total_sprites)
	{
		name = define_sprite_name(&sprites[i]);
		sprites[i].texture.img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr, name,
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
		free (name);
	}
}

void	load_textures(char **path, t_cub *cub, t_game *game)
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
	load_hud(cub, game);
	load_sprites(cub, game->sprites, game->num_sprites);
	//load_skybox(cub, game);
}
