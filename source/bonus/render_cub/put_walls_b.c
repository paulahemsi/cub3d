/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 03:23:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/06 00:55:47 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static void	define_wall_direction(t_game *game, t_ray *rays, int ray)
{
	if (rays[ray].vertical_hit)
	{
		if (rays[ray].left)
			game->wall_direction = EAST;
		else
			game->wall_direction = WEST;
	}
	else
	{
		if (rays[ray].up)
			game->wall_direction = SOUTH;
		else
			game->wall_direction = NORTH;
	}
}

static int	define_texture_offsetX(t_ray *rays, int ray, t_texture texture)
{
	if (rays[ray].vertical_hit)
		return ((int)rays[ray].hit[Y] % texture.width);
	else
		return ((int)rays[ray].hit[X] % texture.width);
}

//!para bônus mexer no offset[X] para dar efeito de tudo se mexendo/tontura.
//!algo por aqui: offset[X] = init[X] * texture.width / cub->game.wall_height;
//!offset[Y] = 1 -> listras verticais
static int	get_texture_color(t_cub *cub, int y, int offset_x)
{
	t_texture	texture;
	int			screen_height;
	int			offset[2];
	int			dist_to_top;

	texture = cub->game.texture[cub->game.wall_direction];
	screen_height = cub->settings.screen[HEIGHT];
	offset[X] = offset_x;// + y;
	dist_to_top = y + (cub->game.wall_height / 2) - (screen_height / 2);
	offset[Y] = dist_to_top * ((float)texture.height / cub->game.wall_height);
	return (*(unsigned int *)(texture.img.data
		+ (offset[Y] * texture.img.line_length + offset[X]
		* (texture.img.bits_per_pixel / 8))));
}

static void	draw_wall(t_cub *cub, int *init, int y_end, int offset_x)
{
	int	color;
	int	y;

	y = init[Y];
	while (y <= y_end)
	{
		if ((y >= 0) && (y <= cub->settings.screen[HEIGHT]))
		{
			color = get_texture_color(cub, y, offset_x);
			if (color != 0x000000)
				put_pixel(&cub->img, init[X], y, color);
		}
		y++;
	}
}

void	put_walls(t_cub *cub, t_ray *rays, t_toggle *t)
{
	int		ray;
	int		init[2];
	int		end_y;
	int		offset_x;

	ray = 0;
	while (ray < cub->game.ray.total)
	{
		cub->game.is_texture = FALSE;
		if (cub->game.win)
			cub->game.is_texture = TRUE;
		if (ft_isalpha(rays[ray].wall_content))//!manter secret com s..??
			cub->game.is_texture = FALSE;
		cub->game.wall_height = ((TILE_SIZE / rays[ray].dist) * cub->game.player.plane_dist);
		init[X] = ray;
		init[Y] = cub->settings.center[Y] - (cub->game.wall_height / 2);
		if (init[Y] < 0)
			init[Y] = 0;
		end_y = cub->settings.center[Y] + (cub->game.wall_height / 2);
		if (end_y > cub->settings.screen[HEIGHT])
			end_y = cub->settings.screen[HEIGHT];
		define_wall_direction(&cub->game, rays, ray);
		offset_x = define_texture_offsetX(rays, ray, cub->game.texture[cub->game.wall_direction]);
		define_wall_colors(cub, rays, ray);
		if (cub->game.is_texture && (t->night_mode != TRUE) && (t->debug != TRUE))
			draw_wall(cub, init, end_y, offset_x);
		else
			put_line(cub, init, init[X], end_y);
		ray++;
	}
}
