/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 03:23:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/15 23:04:48 by phemsi-a         ###   ########.fr       */
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
	shadow = floor((rays[ray].dist / 1000) * 255);
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

void	put_walls(t_cub *cub, t_ray *rays)
{
	int		wall_height;
	int		ray;
	int		init[2];

	ray = 0;
	while (ray < cub->game.ray.total)
	{
		define_wall_colors(cub, rays, ray);
		wall_height = (floor)(TILE_SIZE / rays[ray].dist * cub->game.player.plane_dist);
		if (wall_height > cub->settings.screen[HEIGHT])
			wall_height = cub->settings.screen[HEIGHT];
		init[X] = ray;
		init[Y] = cub->settings.center[Y] - (wall_height / 2) - ((PLAYER_HEIGHT - cub->game.player.height) * 2);
		put_line(cub, init, init[X], init[Y] + wall_height);
		ray++;
	}
}
