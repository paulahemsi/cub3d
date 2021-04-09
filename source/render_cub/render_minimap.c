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


static void	put_player(t_data *img, int *pos)
{
	int line;
	int player_pos[2];

	define_img_colors(img, 200, 200, 200);
	player_pos[X] = pos[X];
	player_pos[Y] = pos[Y];
	while (player_pos[Y] < pos[Y] + 2)
	{
		put_line(img, player_pos, player_pos[X] + 2, player_pos[Y]);
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
	while (tile_pos[Y] < pos[Y] + (TILE_SIZE * SCALE))
	{
		put_line(img, tile_pos, tile_pos[X] + (TILE_SIZE * SCALE), tile_pos[Y]);
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
	horizontal->hitted = 0;
	angle = normalize_angle(angle);
	horizontal->intercept[Y] = floor(cub->player.pos[Y] / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(angle))
	{
		horizontal->intercept[Y] += TILE_SIZE;
		horizontal->step[Y] = TILE_SIZE;
	}
	else
	{
		horizontal->intercept[Y] -= 1;
		horizontal->step[Y] = -TILE_SIZE;
	}
	horizontal->intercept[X] = cub->player.pos[X] + (horizontal->intercept[Y] - cub->player.pos[Y]) / tan(angle);
	horizontal->step[X] = TILE_SIZE / tan(angle);
	if (!(is_ray_facing_right(angle)) && horizontal->step[X] > 0)
		horizontal->step[X] *= -1;
	if (is_ray_facing_right(angle) && horizontal->step[X] < 0)
		horizontal->step[X] *= -1;
	while (horizontal->intercept[X] >= 0 && horizontal->intercept[X] <= cub->world_width && horizontal->intercept[Y] >= 0 && horizontal->intercept[Y] <= cub->world_height)
	{
		if (is_tile_free(horizontal->intercept, cub))
		{
			horizontal->intercept[X] += horizontal->step[X];
			horizontal->intercept[Y] += horizontal->step[Y];
		}
		else
		{
			horizontal->hit[X] = horizontal->intercept[X];
			horizontal->hit[Y] = horizontal->intercept[Y];
			horizontal->content = cub->map.row[(int)floor(horizontal->intercept[Y] / TILE_SIZE)][(int)floor(horizontal->intercept[X] / TILE_SIZE)];
			horizontal->hitted = TRUE;
			break;
		}
	}
}

static void	find_vertical_collision(t_configs *cub, t_cast *vertical, float angle, int column)
{
	vertical->hitted = FALSE;
	angle = normalize_angle(angle);
	vertical->intercept[X] = floor(cub->player.pos[X] / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(angle))
	{
		vertical->intercept[X] += TILE_SIZE;
		vertical->step[X] = TILE_SIZE;
	}
	else
	{
		vertical->intercept[X] -= 1;
		vertical->step[X] = -TILE_SIZE;
	}
	vertical->intercept[Y] = cub->player.pos[Y] + (vertical->intercept[X] - cub->player.pos[X]) * tan(angle);
	vertical->step[Y] = TILE_SIZE * tan(angle);
	if (!(is_ray_facing_down(angle)) && vertical->step[Y] > 0)
		vertical->step[Y] *= -1;
	if (is_ray_facing_down(angle) && vertical->step[Y] < 0)
		vertical->step[Y] *= -1;
	while (vertical->intercept[X] >= 0 && vertical->intercept[X] <= cub->world_width && vertical->intercept[Y] >= 0 && vertical->intercept[Y] <= cub->world_height)
	{
		if (is_tile_free(vertical->intercept, cub))
		{
			vertical->intercept[X] += vertical->step[X];
			vertical->intercept[Y] += vertical->step[Y];
		}
		else
		{
			vertical->hit[X] = vertical->intercept[X];
			vertical->hit[Y] = vertical->intercept[Y];
			vertical->content = cub->map.row[(int)floor(vertical->intercept[Y] / TILE_SIZE)][(int)floor(vertical->intercept[X] / TILE_SIZE)];
			vertical->hitted = TRUE;
			break;
		}
	}
}

static void	store_ray_data(t_ray *rays, t_cast *direction, int column, float angle)
{
		rays[column].dist = direction->distance;
		rays[column].hit[X] = direction->hit[X];
		rays[column].hit[Y] = direction->hit[Y];
		rays[column].wall_content = direction->content;
		rays[column].vertical_hit = FALSE;
		rays[column].angle = angle;
		rays[column].up = !(is_ray_facing_down(angle));
		rays[column].left = !(is_ray_facing_right(angle));
}

static void	cast_ray(t_data *img, float angle, int column, t_ray *rays)
{
	t_cast	horizontal;
	t_cast	vertical;

	find_horizontal_collision(img->cub, &horizontal, angle, column);
	find_vertical_collision(img->cub, &vertical, angle, column);

	if (horizontal.hitted)
		horizontal.distance = calc_distance(img->cub->player.pos, horizontal.hit);
	else
		horizontal.distance = 100000;
	if (vertical.hitted)
		vertical.distance = calc_distance(img->cub->player.pos, vertical.hit);
	else
		vertical.distance = 100000;
	float distance;
	if (horizontal.distance < vertical.distance)
		store_ray_data(rays, &horizontal, column, angle);
	else
		store_ray_data(rays, &vertical, column, angle);
}

static void	cast_all_rays(t_data *img, t_configs *cub, t_ray *rays)
{
	float angle;
	int	column;

	angle = cub->player.angle - HALF_FOV;
	while (column < cub->screen_width)
	{
		cast_ray(img, angle, column, rays);
		angle += FOV / (cub->screen_width);
		column++;
	}
}

static void	render_rays(t_data *img, t_configs *cub)
{
	t_ray	rays[img->cub->screen_width];
	int		ray;
	int		player_pos[2];

	cast_all_rays(img, cub, rays);
	ray = 0;
	player_pos[X] = cub->player.pos[X] * SCALE;
	player_pos[Y] = cub->player.pos[Y] * SCALE;
	while (ray < img->cub->screen_width)
	{
		put_line(img, player_pos, rays[ray].hit[X] * SCALE, rays[ray].hit[Y] * SCALE);
		ray++;
	}
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
			tile_pos[X] = (column * TILE_SIZE) * SCALE;
			tile_pos[Y] = (line * TILE_SIZE) * SCALE;
			if (img->cub->map.row[line][column] == '1')
				put_tile(img, tile_pos);
			column++;
		}
		line++;
	}
	render_player(img, &img->cub->player);
	render_rays(img, img->cub);
}
