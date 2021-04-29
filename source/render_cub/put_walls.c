/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 03:23:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/29 22:34:41 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	define_wall_direction(t_render *game, t_ray *rays, int ray)
{
	if (rays[ray].vertical_hit)
	{
		if (rays[ray].left)
			game->wall = EAST;
		else
			game->wall = WEST;

	}
	else
	{
		if (rays[ray].up)
			game->wall = SOUTH;
		else
			game->wall = NORTH;
	}
}

static int	define_texture_offsetX(t_ray *rays, int ray, t_texture texture)
{
	if (rays[ray].vertical_hit)
		return ((int)rays[ray].hit[Y] % texture.width);
	else
		return ((int)rays[ray].hit[X] % texture.width);
}

static int	get_texture_color(int *init, t_cub *cub, int y, int offset_x)
{
	t_texture	texture;
	int			offset[2];
	
	texture = cub->game.texture[cub->game.wall];
	offset[X] = offset_x;
	//!para bônus mexer no offset[X] para dar efeito de tudo se mexendo/tontura. algo por aqui: offset[X] = init[X] * texture.width / cub->game.wall_height;
	//!offset[Y] = 1 -> listras verticais
	//offset[X] = init[X] * texture.width / cub->game.wall_height;
	int dist_to_top = y + (cub->game.wall_height / 2) - (cub->settings.screen[HEIGHT] / 2);
	offset[Y] = dist_to_top * ((float)texture.height / cub->game.wall_height);
	return (*(unsigned int *)(texture.img.data + (offset[Y] * texture.img.line_length + offset[X] * (texture.img.bits_per_pixel / 8))));
}

static void	draw_wall(t_cub *cub, int *init, int y_end, int offset_x)
{
	int color;
	int y;

	y = init[Y];
	while (y <= y_end)
	{
		if ((y >= 0) && (y <= cub->settings.screen[HEIGHT]))
		{
			color = get_texture_color(init, cub, y, offset_x);
			put_pixel(&cub->img, init[X], y, color);
		}
		y++;
	}
}

void	put_walls(t_cub *cub, t_ray *rays)
{
	int		ray;
	int		init[2];

	ray = 0;
	cub->game.is_texture = FALSE;
	while (ray < cub->game.ray.total)
	{
		cub->game.wall_height = ((TILE_SIZE / rays[ray].dist) * cub->game.player.plane_dist);
		init[X] = ray;
		init[Y] = cub->settings.center[Y] - (cub->game.wall_height / 2);
		if (init[Y] < 0)
			init[Y] = 0;
		int end_y = cub->settings.center[Y] + (cub->game.wall_height / 2);
		if (end_y > cub->settings.screen[HEIGHT])
			end_y = cub->settings.screen[HEIGHT];
		define_wall_direction(&cub->game, rays, ray);
		int offset_x = define_texture_offsetX(rays, ray, cub->game.texture[cub->game.wall]);
		define_wall_colors(cub, rays, ray);
		if (cub->game.is_texture && (cub->toggle.night_mode != TRUE) && (cub->toggle.debug != TRUE))
			draw_wall(cub, init, end_y, offset_x);
		else
			put_line(cub, init, init[X], end_y);
		ray++;
	}
	cub->game.is_texture = FALSE;
}
