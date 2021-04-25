/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:08:11 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/25 00:19:47 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	save_hit(t_cast *direction, t_cub *cub, float *to_check_tile)
{
	int	col;
	int	row;

	col = (int)floor(to_check_tile[Y] / TILE_SIZE);
	row = (int)floor(to_check_tile[X] / TILE_SIZE);
	direction->hit[X] = direction->intercept[X];
	direction->hit[Y] = direction->intercept[Y];
	//!DEU UM SEGV READ UNKNOW ADDRESS AQUI:
	direction->content = cub->game.map.row[col][row];
	direction->hitted = TRUE;
}

static void	increment(t_cast *direction)
{
	direction->intercept[X] += direction->step[X];
	direction->intercept[Y] += direction->step[Y];
}

static void	define_ray_values(t_cast *direction, t_cub *cub,
		int dir, int pos_axis)
{
	int	axis;

	if (dir == HOR)
		axis = Y;
	else
		axis = X;
	direction->hitted = FALSE;
	direction->intercept[axis] = floor(cub->game.player.pos[axis] / TILE_SIZE) * TILE_SIZE;
	if (pos_axis)
	{
		direction->intercept[axis] += TILE_SIZE;
		direction->step[axis] = TILE_SIZE;
	}
	else
		direction->step[axis] = -TILE_SIZE;
}

static void	sprite_collision(t_render *game, float *to_check_tile)
{
	int i;

	i = 0;
	while (i < game->num_sprites)
	{
		if ((game->sprites[i].pos[X] == (int)floor(to_check_tile[X])) && (game->sprites[i].pos[Y] == (int)floor(to_check_tile[Y])))
			game->sprites[i].visible = TRUE;
		i++;
	}
	if (game->sprite == FALSE)
		game->sprite = TRUE;
}

void	find_horizontal_collision(t_cub *cub, t_cast *horizontal, float angle, int column)
{
	float	to_check_tile[2];

	define_ray_values(horizontal, cub, HOR, is_ray_facing_down(angle));
	horizontal->intercept[X] = cub->game.player.pos[X] + (horizontal->intercept[Y] - cub->game.player.pos[Y]) / tan(angle);
	horizontal->step[X] = TILE_SIZE / tan(angle);
	if (!(is_ray_facing_right(angle)) && horizontal->step[X] > 0)
		horizontal->step[X] *= TOGGLE;
	if (is_ray_facing_right(angle) && horizontal->step[X] < 0)
		horizontal->step[X] *= TOGGLE;
	while (is_inside_world_limits(horizontal->intercept, cub->settings.world))
	{
		to_check_tile[X] = horizontal->intercept[X];
		to_check_tile[Y] = horizontal->intercept[Y];
		if (!(is_ray_facing_down(angle)))
			to_check_tile[Y] -= 1;
		if (hit_sprite(to_check_tile, &cub->settings, &cub->game.map))
			sprite_collision(&cub->game, to_check_tile);
		if (is_tile_free(to_check_tile, &cub->settings, &cub->game.map, FALSE))
			increment(horizontal);
		else
		{
			save_hit(horizontal, cub, to_check_tile);
			break ;
		}
	}
}

void	find_vertical_collision(t_cub *cub, t_cast *vertical, float angle, int column)
{
	float	to_check_tile[2];

	define_ray_values(vertical, cub, VER, is_ray_facing_right(angle));
	vertical->intercept[Y] = cub->game.player.pos[Y] + (vertical->intercept[X] - cub->game.player.pos[X]) * tan(angle);
	vertical->step[Y] = TILE_SIZE * tan(angle);
	if (!(is_ray_facing_down(angle)) && vertical->step[Y] > 0)
		vertical->step[Y] *= TOGGLE;
	if (is_ray_facing_down(angle) && vertical->step[Y] < 0)
		vertical->step[Y] *= TOGGLE;
	while (is_inside_world_limits(vertical->intercept, cub->settings.world))
	{
		to_check_tile[X] = vertical->intercept[X];
		to_check_tile[Y] = vertical->intercept[Y];
		if (!(is_ray_facing_right(angle)))
			to_check_tile[X] -= 1;
		if (hit_sprite(to_check_tile, &cub->settings, &cub->game.map))
			sprite_collision(&cub->game, to_check_tile);
		if (is_tile_free(to_check_tile, &cub->settings, &cub->game.map, FALSE))
			increment(vertical);
		else
		{
			save_hit(vertical, cub, to_check_tile);
			break ;
		}
	}
}
