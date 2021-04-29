/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 02:22:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/29 23:03:46 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	free_map(char **map)
{
	size_t	i;

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

void	free_paths(char **path)
{
	int	texture;

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
}

static void	free_textures(t_cub *cub, t_texture *textures, t_sprite *sprites)
{
	int	i;

	if (textures)
	{
		i = NORTH;
		while (i <= WEST)
		{
			mlx_destroy_image(cub->mlx_ptr, textures[i].img.ptr);
			i++;
		}
		free(textures);
	}
	if (sprites)
	{
		i = 0;
		while (i < cub->game.num_sprites)
		{
			mlx_destroy_image(cub->mlx_ptr, sprites[i].texture.img.ptr);
			i++;
		}
		free(sprites);
	}
	if (cub->game.hud.img.ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->game.hud.img.ptr);
}

void	free_cub(t_cub *cub)
{
	free_paths(cub->settings.path);
	free_map(cub->game.map.row);
	free_textures(cub, cub->game.texture, cub->game.sprites);
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
