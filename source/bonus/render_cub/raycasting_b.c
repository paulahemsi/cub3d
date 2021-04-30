/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:28:34 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 21:11:45 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static void	copy_last_ray(t_ray *ray, int col)
{
	ray[col].dist = ray[col - 1].dist;
	ray[col].hit[X] = ray[col - 1].hit[X];
	ray[col].hit[Y] = ray[col - 1].hit[Y];
	ray[col].wall_content = ray[col - 1].wall_content;
	ray[col].angle = ray[col - 1].angle;
	ray[col].up = ray[col - 1].up;
	ray[col].left = ray[col - 1].left;
	ray[col].vertical_hit = ray[col - 1].vertical_hit;
}

static void	store_ray_data(t_ray *ray, t_cast *direction, int col, float angle)
{
	ray[col].dist = direction->distance;
	ray[col].hit[X] = direction->hit[X];
	ray[col].hit[Y] = direction->hit[Y];
	ray[col].wall_content = direction->content;
	ray[col].angle = angle;
	ray[col].up = is_ray_facing(UP, angle);
	ray[col].left = is_ray_facing(LEFT, angle);
}

static void	find_closest_wall(t_cast *h, t_cast *v, t_player *player, float a)
{
	float	fish_eye;

	fish_eye = cos(player->angle - a);
	if (h->hitted)
		h->distance = hit_distance(player->pos, h->hit) * fish_eye;
	else
		h->distance = INT_MAX;
	if (v->hitted)
		v->distance = hit_distance(player->pos, v->hit) * fish_eye;
	else
		v->distance = INT_MAX;
}

static void	cast_ray(t_cub *cub, float angle, int column, t_ray *rays)
{
	t_cast	horizontal;
	t_cast	vertical;

	find_horizontal_collision(cub, &horizontal, angle);
	find_vertical_collision(cub, &vertical, angle);
	find_closest_wall(&horizontal, &vertical, &cub->game.player, angle);
	if (horizontal.distance < vertical.distance)
	{
		store_ray_data(rays, &horizontal, column, angle);
		rays[column].vertical_hit = FALSE;
	}
	else if (horizontal.distance > vertical.distance)
	{
		store_ray_data(rays, &vertical, column, angle);
		rays[column].vertical_hit = TRUE;
	}
	else if ((column - 1) >= 0)
		copy_last_ray(rays, column);
}

void	raycasting(t_cub *cub, t_ray *rays)
{
	float	angle;
	int		pixel_column;

	angle = cub->game.player.angle - HALF_FOV;
	pixel_column = 0;
	while (pixel_column < cub->settings.screen[WIDTH])
	{
		angle = normalize_angle(angle);
		cast_ray(cub, angle, pixel_column, rays);
		angle += cub->game.ray.step;
		pixel_column++;
	}
}
