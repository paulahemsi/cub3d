/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 02:22:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/07 19:59:49 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static void	free_paths_and_map(char **path, char **map)
{
	int		texture;
	size_t	i;

	texture = NORTH;
	while (texture <= WEST)
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
			map[i] = NULL;
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
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (cub->game.hud[i].img.ptr)
			mlx_destroy_image(cub->mlx_ptr, cub->game.hud[i].img.ptr);
		i++;
	}
	i = 0;
	while (i <= 3)
	{
		if (cub->game.hearts[i].img.ptr)
			mlx_destroy_image(cub->mlx_ptr, cub->game.hearts[i].img.ptr);
		i++;
	}
}

void	free_cub(t_cub *cub)
{
	if (cub->settings.line)
		free (cub->settings.line);
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
