/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:28:34 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/12 00:55:14 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	is_ray_facing_down(float	angle)
{
	if (angle > 0 && angle < PI)
		return (TRUE);
	else
		return (FALSE);
}

static int	is_ray_facing_right(float	angle)
{
	if (angle < PI / 2 || angle > 1.5 * PI)
		return (TRUE);
	else
		return (FALSE);
}

static void	find_horizontal_collision(t_configs *cub, t_cast *horizontal, float angle, int column)
{
	horizontal->hitted = FALSE;
	horizontal->intercept[Y] = floor(cub->player.pos[Y] / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(angle))
	{
		horizontal->intercept[Y] += TILE_SIZE;
		horizontal->step[Y] = TILE_SIZE;
	}
	else
	{
		//!horizontal->intercept[Y] -= 1;
		horizontal->step[Y] = -TILE_SIZE;
	}
	horizontal->intercept[X] = cub->player.pos[X] + (horizontal->intercept[Y] - cub->player.pos[Y]) / tan(angle);
	horizontal->step[X] = TILE_SIZE / tan(angle);
	if (!(is_ray_facing_right(angle)) && horizontal->step[X] > 0)
		horizontal->step[X] *= TOGGLE;
	if (is_ray_facing_right(angle) && horizontal->step[X] < 0)
		horizontal->step[X] *= TOGGLE;
	while (horizontal->intercept[X] >= 0 && horizontal->intercept[X] <= cub->world_width && horizontal->intercept[Y] >= 0 && horizontal->intercept[Y] <= cub->world_height)
	{
		float	to_check_tile[2];

		to_check_tile[X] = horizontal->intercept[X];
		to_check_tile[Y] = horizontal->intercept[Y];
		if (!(is_ray_facing_down(angle)))
			to_check_tile[Y] -= 1;
		if (is_tile_free(to_check_tile, cub))
		{
			horizontal->intercept[X] += horizontal->step[X];
			horizontal->intercept[Y] += horizontal->step[Y];
		}
		else
		{
			horizontal->hit[X] = horizontal->intercept[X];
			horizontal->hit[Y] = horizontal->intercept[Y];
			horizontal->content = cub->map.row[(int)floor(to_check_tile[Y] / TILE_SIZE)][(int)floor(to_check_tile[X] / TILE_SIZE)];
			horizontal->hitted = TRUE;
			break;
		}
	}
}

static void	find_vertical_collision(t_configs *cub, t_cast *vertical, float angle, int column)
{
	float	to_check_tile[2];

	vertical->hitted = FALSE;
	vertical->intercept[X] = floor(cub->player.pos[X] / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(angle))
	{
		vertical->intercept[X] += TILE_SIZE;
		vertical->step[X] = TILE_SIZE;
	}
	else
		vertical->step[X] = -TILE_SIZE;
	vertical->intercept[Y] = cub->player.pos[Y] + (vertical->intercept[X] - cub->player.pos[X]) * tan(angle);
	vertical->step[Y] = TILE_SIZE * tan(angle);
	if (!(is_ray_facing_down(angle)) && vertical->step[Y] > 0)
		vertical->step[Y] *= TOGGLE;
	if (is_ray_facing_down(angle) && vertical->step[Y] < 0)
		vertical->step[Y] *= TOGGLE;
	while (vertical->intercept[X] >= 0 && vertical->intercept[X] <= cub->world_width && vertical->intercept[Y] >= 0 && vertical->intercept[Y] <= cub->world_height)
	{
		to_check_tile[X] = vertical->intercept[X];
		to_check_tile[Y] = vertical->intercept[Y];
		if (!(is_ray_facing_right(angle)))
			to_check_tile[X] -= 1;
		if (is_tile_free(to_check_tile, cub))
		{
			vertical->intercept[X] += vertical->step[X];
			vertical->intercept[Y] += vertical->step[Y];
		}
		else
		{
			vertical->hit[X] = vertical->intercept[X];
			vertical->hit[Y] = vertical->intercept[Y];
			vertical->content = cub->map.row[(int)floor(to_check_tile[Y] / TILE_SIZE)][(int)floor(to_check_tile[X] / TILE_SIZE)];
			vertical->hitted = TRUE;
			break;
		}
	}
}

static void	copy_last_ray(t_ray *rays, int column, float angle)
{
	rays[column].dist = rays[column - 1].dist;
	rays[column].hit[X] = rays[column - 1].hit[X];
	rays[column].hit[Y] = rays[column - 1].hit[Y];
	rays[column].wall_content = rays[column - 1].wall_content;
	rays[column].angle = rays[column - 1].angle;
	rays[column].up = rays[column - 1].up;
	rays[column].left = rays[column - 1].left;
	rays[column].vertical_hit = rays[column - 1].vertical_hit;
}

static void	store_ray_data(t_ray *rays, t_cast *direction, int column, float angle)
{
	rays[column].dist = direction->distance;
	rays[column].hit[X] = direction->hit[X];
	rays[column].hit[Y] = direction->hit[Y];
	rays[column].wall_content = direction->content;
	rays[column].angle = angle;
	rays[column].up = !(is_ray_facing_down(angle));
	rays[column].left = !(is_ray_facing_right(angle));
}

static void	cast_ray(t_data *img, float angle, int column, t_ray *rays)
{
	t_cast	horizontal;
	t_cast	vertical;
	float	fish_eye_correction;

	angle = normalize_angle(angle);
	find_horizontal_collision(img->cub, &horizontal, angle, column);
	find_vertical_collision(img->cub, &vertical, angle, column);
	fish_eye_correction = cos(img->cub->player.angle - angle);
	if (horizontal.hitted)
		horizontal.distance = (float)floor(calc_distance(img->cub->player.pos, horizontal.hit) * fish_eye_correction);
	else
		horizontal.distance = INT_MAX;
	if (vertical.hitted)
		vertical.distance = (float)floor(calc_distance(img->cub->player.pos, vertical.hit) * fish_eye_correction);
	else
		vertical.distance = INT_MAX;
	float distance;
	if (horizontal.distance < vertical.distance)
	{
		store_ray_data(rays, &horizontal, column, angle);
		rays[column].vertical_hit = FALSE;
	}
	else //if (vertical.distance < horizontal.distance)
	{
		store_ray_data(rays, &vertical, column, angle);
		rays[column].vertical_hit = TRUE;
	}
	//else
		//copy_last_ray(rays, column, angle);
}

void	raycasting(t_data *img, t_configs *cub, t_ray *rays)
{
	float angle;
	int	column;

	angle = cub->player.angle - HALF_FOV;
	column = 0;
	while (column < cub->ray.total)
	{
		cast_ray(img, angle, column, rays);
		angle += cub->ray.step;
		column++;
	}
}
