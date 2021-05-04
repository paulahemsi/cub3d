/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:13:10 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/04 14:30:43 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static char	*define_name(int texture, int id)
{
	char	*name;
	char	*aux;

	name = ft_itoa(id);
	if (texture == SPRITE)
		aux = ft_strjoin("./textures/sprites/sprite", name);
	else if (texture == HUD)
		aux = ft_strjoin("./textures/hud/hud_", name);
	else
		aux = ft_strjoin("./textures/hud/hearts_", name);
	free(name);
	name = ft_strjoin(aux, ".XPM");
	free(aux);
	return (name);
}

static void	load_life_bar(t_cub *cub, t_game *game)
{
	int i;
	char *name;

	i = 0;
	while (i <= 3)
	{
		name = define_name(HEARTS, i);
		game->hearts[i].img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr, name,
				&game->hearts[i].width, &game->hearts[i].height);
		game->hearts[i].img.data = mlx_get_data_addr(game->hearts[i].img.ptr,
				&game->hearts[i].img.bits_per_pixel,
				&game->hearts[i].img.line_length,
				&game->hearts[i].img.endian);
		i++;
		free (name);
	}
}

static void	load_hud(t_cub *cub, t_game *game)
{
	int i;
	char *name;

	i = 0;
	while (i <= 7)
	{
		name = define_name(HUD, i);
		game->hud[i].img.ptr = mlx_xpm_file_to_image(cub->mlx_ptr, name,
				&game->hud[i].width, &game->hud[i].height);
		game->hud[i].img.data = mlx_get_data_addr(game->hud[i].img.ptr,
				&game->hud[i].img.bits_per_pixel,
				&game->hud[i].img.line_length,
				&game->hud[i].img.endian);
		i++;
		free (name);
	}
}

static void	load_sprites(t_cub *cub, t_sprite *sprites, int total_sprites)
{
	int		i;
	char	*name;

	i = 0;
	while (i < total_sprites)
	{
		name = define_name(SPRITE, sprites[i].id);
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
	load_life_bar(cub, game);
	load_sprites(cub, game->sprites, game->num_sprites);
	//load_skybox(cub, game);
}
