/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 02:22:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 14:04:58 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	free_paths_and_map(char **path, char **map)
{
	int		texture;
	size_t	i;

	texture = NORTH;
	while (texture <= SPRITE)
	{
		if (path[texture])
		{
			free(path[texture]);
			path[texture] = NULL;
		}
		texture++;
	}
	if (map)
	{
		i = 0;
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

static void	free_textures(t_cub *cub, t_texture *wall_text, t_sprite *sprites)
{
	int	i;

	if (wall_text)
	{
		i = NORTH;
		while (i <= WEST)
		{
			if (wall_text[i].img.ptr)
				mlx_destroy_image(cub->mlx_ptr, wall_text[i].img.ptr);
			i++;
		}
		free(wall_text);
	}
	if (sprites)
	{
		i = 0;
		while (i < cub->game.num_sprites)
		{
			if (sprites[i].texture.img.ptr)
				mlx_destroy_image(cub->mlx_ptr, sprites[i].texture.img.ptr);
			i++;
		}
		free(sprites);
	}
}

static void	free_hud(t_cub *cub)
{
	if (cub->game.hud.img.ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->game.hud.img.ptr);
}

void	free_cub(t_cub *cub)
{
	free_paths_and_map(cub->settings.path, cub->game.map.row);
	free_textures(cub, cub->game.texture, cub->game.sprites);
	free_hud(cub);
	if (cub->img.ptr && cub->mlx_ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->img.ptr);
	if (cub->window_ptr && cub->mlx_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->window_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
}

int	close_cub(t_cub *cub)
{
	free_cub(cub);
	exit(0);
}
