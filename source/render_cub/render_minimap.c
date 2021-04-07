/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:23:03 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/06 23:53:38 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"


static void	render_rays(t_data *img)
{

}



static void	put_player(t_data *img, int *pos)
{
	int line;
	int player_pos[2];

	define_img_colors(img, 200, 200, 200);
	player_pos[X] = pos[X];
	player_pos[Y] = pos[Y];
	while (player_pos[Y] < pos[Y] + (img->cub->map.tile_size[Y] * SCALE * SCALE))
	{
		put_line(img, player_pos, player_pos[X] + (img->cub->map.tile_size[X] * SCALE * SCALE), player_pos[Y]);
		player_pos[Y]++;
	}
	put_line(img, player_pos, player_pos[X] + cos(img->cub->player.angle) * 20, player_pos[Y] + sin(img->cub->player.angle) * 20);
}

static void	put_tile(t_data *img, int *pos)
{
	int line;
	int tile_pos[2];

	define_img_colors(img, 30, 0, 70);
	tile_pos[X] = pos[X];
	tile_pos[Y] = pos[Y];
	while (tile_pos[Y] < pos[Y] + (img->cub->map.tile_size[Y] * SCALE))
	{
		put_line(img, tile_pos, tile_pos[X] + (img->cub->map.tile_size[X] * SCALE), tile_pos[Y]);
		tile_pos[Y]++;
	}
}

static void	render_player(t_data *img, t_player *player)
{
	int player_pos[2];

	player_pos[X] = player->pos[X] * SCALE;
	player_pos[Y] = player->pos[Y] * SCALE;
	put_player(img, player_pos);
}

void	render_minimap(t_data *img)
{
	int	line;
	int column;
	int tile_pos[2];

	line = 0;
	while (line < img->cub->map.total_row)
	{
		column = 0;
		while (column < img->cub->map.total_column)
		{
			tile_pos[X] = (column * img->cub->map.tile_size[X]) * SCALE;
			tile_pos[Y] = (line * img->cub->map.tile_size[Y]) * SCALE;
			if (img->cub->map.row[line][column] == '1')
				put_tile(img, tile_pos);
			column++;
		}
		line++;
	}
	render_player(img, &img->cub->player);
}
