/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:08:11 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 21:13:59 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

static void	save_hit(t_cast *direction, t_cub *cub, float *to_check_tile)
{
	int	col;
	int	row;

	col = (int)floor(to_check_tile[Y] / TILE_SIZE);
	row = (int)floor(to_check_tile[X] / TILE_SIZE);
	direction->hit[X] = direction->intercept[X];
	direction->hit[Y] = direction->intercept[Y];
	direction->content = cub->game.map.row[col][row];
	direction->hitted = TRUE;
}

static void	increment(t_cast *direction)
{
	direction->intercept[X] += direction->step[X];
	direction->intercept[Y] += direction->step[Y];
}

static void	define_ray_values(t_cast *ray, t_cub *cub,
		int direction, int positive_direction)
{
	int			axis;
	t_player	*player;

	player = &cub->game.player;
	if (direction == HOR)
		axis = Y;
	else
		axis = X;
	ray->hitted = FALSE;
	ray->intercept[axis] = ((player->pos[axis] / TILE_SIZE) * TILE_SIZE);
	if (!positive_direction)
		ray->intercept[axis] -= 0.0001;
	if (positive_direction)
	{
		ray->intercept[axis] += TILE_SIZE;
		ray->step[axis] = TILE_SIZE;
	}
	else
		ray->step[axis] = -TILE_SIZE;
}

void	find_horizontal_collision(t_cub *cub, t_cast *horizontal, float angle)
{
	float	to_check_tile[2];
	float	diff_y;

	define_ray_values(horizontal, cub, HOR, is_ray_facing(DOWN, angle));
	diff_y = horizontal->intercept[Y] - cub->game.player.pos[Y];
	horizontal->intercept[X] = cub->game.player.pos[X] + diff_y / tan(angle);
	horizontal->step[X] = TILE_SIZE / tan(angle);
	if (is_ray_facing(LEFT, angle) && horizontal->step[X] > 0)
		horizontal->step[X] *= TOGGLE;
	if (is_ray_facing(RIGHT, angle) && horizontal->step[X] < 0)
		horizontal->step[X] *= TOGGLE;
	while (is_inside_world_limits(horizontal->intercept, cub->settings.world))
	{
		to_check_tile[X] = horizontal->intercept[X];
		to_check_tile[Y] = horizontal->intercept[Y];
		if (is_ray_facing(UP, angle))
			to_check_tile[Y] -= 1;
		if (has_wall(to_check_tile, &cub->settings, &cub->game.map))
		{
			save_hit(horizontal, cub, to_check_tile);
			break ;
		}
		else
			increment(horizontal);
	}
}

void	find_vertical_collision(t_cub *cub, t_cast *vertical, float angle)
{
	float	to_check_tile[2];
	float	diff_x;

	define_ray_values(vertical, cub, VER, is_ray_facing(RIGHT, angle));
	diff_x = vertical->intercept[X] - cub->game.player.pos[X];
	vertical->intercept[Y] = cub->game.player.pos[Y] + diff_x * tan(angle);
	vertical->step[Y] = TILE_SIZE * tan(angle);
	if (is_ray_facing(UP, angle) && vertical->step[Y] > 0)
		vertical->step[Y] *= TOGGLE;
	if (is_ray_facing(DOWN, angle) && vertical->step[Y] < 0)
		vertical->step[Y] *= TOGGLE;
	while (is_inside_world_limits(vertical->intercept, cub->settings.world))
	{
		to_check_tile[X] = vertical->intercept[X];
		to_check_tile[Y] = vertical->intercept[Y];
		if (is_ray_facing(LEFT, angle))
			to_check_tile[X] -= 1;
		if (has_wall(to_check_tile, &cub->settings, &cub->game.map))
		{
			save_hit(vertical, cub, to_check_tile);
			break ;
		}
		else
			increment(vertical);
	}
}
