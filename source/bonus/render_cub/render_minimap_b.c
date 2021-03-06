/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:23:03 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/06 00:56:12 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static void	put_tile(t_cub *cub, int *pos)
{
	int	tile_pos[2];

	if (cub->toggle.night_mode == TRUE)
		define_img_colors(&cub->game.color, 2, 2, 2);
	else
		define_img_colors(&cub->game.color, 22, 22, 22);
	tile_pos[X] = pos[X];
	tile_pos[Y] = pos[Y];
	while (tile_pos[Y] < pos[Y] + (TILE_SIZE * SCALE))
	{
		put_line(cub, tile_pos, tile_pos[X] + (TILE_SIZE * SCALE), tile_pos[Y]);
		tile_pos[Y]++;
	}
}

static void	render_rays(t_cub *cub, t_ray *rays)
{
	int		ray;
	int		player_pos[2];

	ray = 0;
	if (cub->toggle.night_mode == TRUE)
		define_img_colors(&cub->game.color, 123, 246, 18);
	else
		define_img_colors(&cub->game.color, 255, 255, 255);
	player_pos[X] = cub->game.player.pos[X] * SCALE;
	player_pos[Y] = cub->game.player.pos[Y] * SCALE;
	while (ray < cub->settings.screen[WIDTH])
	{
		put_line(cub, player_pos, rays[ray].hit[X] * SCALE,
			rays[ray].hit[Y] * SCALE);
		ray++;
	}
}

void	render_minimap(t_cub *cub, t_map *map, t_ray *rays)
{
	int	line;
	int	column;
	int	tile_pos[2];

	line = 0;
	while (line < map->total_row)
	{
		column = 0;
		while (column < map->total_column)
		{
			tile_pos[X] = (column * TILE_SIZE) * SCALE;
			tile_pos[Y] = (line * TILE_SIZE) * SCALE;
			if (map->row[line][column] == '1')
				put_tile(cub, tile_pos);
			else if (ft_isalpha(map->row[line][column]))
				put_tile(cub, tile_pos);
			column++;
		}
		line++;
	}
	render_rays(cub, rays);
}
