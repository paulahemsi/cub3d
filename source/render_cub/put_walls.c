/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 03:23:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/28 16:44:19 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	toggle_debug_colors(t_rgb *color, t_ray *rays, int ray)
{
	if (rays[ray].vertical_hit)
	{
		if (rays[ray].left)
		{
			if (rays[ray].wall_content == '3')
				define_img_colors(color, 216, 56, 89);
			else
				define_img_colors(color, 226, 66, 99);
		}
		else
		{
			if (rays[ray].wall_content == '3')
				define_img_colors(color, 234, 170, 50);
			else
				define_img_colors(color, 244, 180, 60);
		}
	}
	else
	{
		if (rays[ray].up)
		{
			if (rays[ray].wall_content == '3')
				define_img_colors(color, 54, 133, 128);
			else
				define_img_colors(color, 64, 143, 138);
		}
		else
		{
			if (rays[ray].wall_content == '3')
				define_img_colors(color, 227, 101, 39);
			else
				define_img_colors(color, 237, 111, 49);
		}
	}
}

static void	toggle_night_mode(t_rgb *color, t_ray *rays, int ray)
{
	if (rays[ray].vertical_hit)
	{
		if (rays[ray].left)
		{
			if (rays[ray].wall_content == '3')
				define_img_colors(color, 123, 246, 18);
			else
				define_img_colors(color, 20, 116, 0);
		}
		else
		{
			if (rays[ray].wall_content == '3')
				define_img_colors(color, 123, 246, 18);
			else
				define_img_colors(color, 27, 123, 0);
		}
	}
	else
	{
		if (rays[ray].up)
		{
			if (rays[ray].wall_content == '3')
				define_img_colors(color, 123, 246, 18);
			else
				define_img_colors(color, 62, 180, 6);
		}
		else
		{
			if (rays[ray].wall_content == '3')
				define_img_colors(color, 123, 246, 18);
			else
				define_img_colors(color, 94, 211, 8);
		}
	}
}

static void	define_wall_colors(t_cub *cub, t_ray *rays, int ray)
{
	int	shadow;
	int color;
	int longest_side;

	if (cub->settings.world[HEIGHT] > cub->settings.world[WIDTH])
		longest_side = cub->settings.world[HEIGHT];
	else
		longest_side = cub->settings.world[WIDTH];
	color = 255;
	shadow = floor((rays[ray].dist / 500) * 255);
	color -= shadow;
	if (color > 200)
		color = 200;
	else if (color < 0)
		color = 0;
	define_img_colors(&cub->game.color, color, color, color);
	if (cub->toggle.debug == TRUE)
		toggle_debug_colors(&cub->game.color, rays, ray);
	if (cub->toggle.night_mode == TRUE)
		toggle_night_mode(&cub->game.color, rays, ray);
}

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
	cub->game.is_texture = TRUE;
	while (ray < cub->game.ray.total)
	{
		cub->game.wall_height = ((TILE_SIZE / rays[ray].dist) * cub->game.player.plane_dist);
		//if (cub->game.wall_height > cub->settings.screen[HEIGHT])
		//	cub->game.wall_height = cub->settings.screen[HEIGHT];
		init[X] = ray;
		init[Y] = cub->settings.center[Y] - (cub->game.wall_height / 2);// - ((PLAYER_HEIGHT - cub->game.player.height) * 2);
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
