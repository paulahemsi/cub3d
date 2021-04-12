/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 03:23:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/12 00:52:58 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	toggle_debug_colors(t_data *img, t_ray *rays, int ray)
{
	if (rays[ray].vertical_hit)
	{
		if (rays[ray].left)
			define_img_colors(img, 226, 66, 99);
		else
			define_img_colors(img, 244, 180, 60);	
	}
	else
	{
		if (rays[ray].up)		
			define_img_colors(img, 64, 143, 138);
		else
			define_img_colors(img, 237, 111, 49);
	}
}

static void	define_wall_colors(t_data *img, t_ray *rays, int ray)
{
	int	shadow;
	int color;
	int longest_side;

	if (img->cub->world_height > img->cub->world_width)
		longest_side = img->cub->world_height;
	else
		longest_side = img->cub->world_width;
	color = 255;
	shadow = floor((rays[ray].dist / 1000) * 255);
	color -= shadow;
	if (color > 200)
		color = 200;
	else if (color < 0)
		color = 0;
	define_img_colors(img, color, color, color);
	if (img->cub->debug == TRUE)
		toggle_debug_colors(img, rays, ray);
}

void	put_walls(t_data *img, t_ray *rays)
{
	int		wall_height;
	int		ray;
	int		init[2];

	ray = 0;
	while (ray < img->cub->ray.total)
	{
		define_wall_colors(img, rays, ray);
		wall_height = (floor)(TILE_SIZE / rays[ray].dist * img->cub->player.plane_dist);
		if (wall_height > img->cub->screen_height)
			wall_height = img->cub->screen_height;
		init[X] = ray;
		init[Y] = img->cub->center[Y] - (wall_height / 2) - ((PLAYER_HEIGHT - img->cub->player.height) * 2);
		put_line(img, init, init[X], init[Y] + wall_height);
		ray++;
	}
}
