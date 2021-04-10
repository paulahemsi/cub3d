/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 03:23:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/10 08:00:30 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	define_wall_colors(t_data *img, t_ray *rays, int ray)
{
	if (rays[ray].vertical_hit)
		if (rays[ray].left)
			define_img_colors(img, 0, 10, 50);
		else
			define_img_colors(img, 20, 20, 50);
	else
		if (rays[ray].up)		
			define_img_colors(img, 30, 30, 70);
		else
			define_img_colors(img, 10, 10, 10);
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
		init[Y] = img->cub->center[Y] - (wall_height / 2);// - ((PLAYER_HEIGHT - img->cub->player.height) * 2);
		put_line(img, init, init[X], init[Y] + wall_height);
		ray++;
	}
}
