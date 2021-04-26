/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:01:20 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/26 18:10:17 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

// float	degrees_to_radians(int degree)
// {
// 	return ((float)degree * PI / 180);
// }

// int		radiands_to_degrees(float radian)
// {
// 	return (floor(radian * 180 / PI));
// }

void	define_img_colors(t_rgb *color, int red, int green, int blue)
{
	color->red = red;
	color->green = green;
	color->blue = blue;
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}

int	is_ray_facing_down(float angle)
{
	if (angle > 0 && angle < PI)
		return (TRUE);
	else
		return (FALSE);
}

int	is_ray_facing_right(float angle)
{
	if (angle < PI / 2 || angle > 1.5 * PI)
		return (TRUE);
	else
		return (FALSE);
}

int		hit_sprite(float *pos, t_settings *set, t_map *map)
{
	int minimap[2];

	if (pos[X] < 0 || pos[X] >= set->world[WIDTH] || pos[Y] < 0 || pos[Y] >= set->world[HEIGHT])
		return (FALSE);
	minimap[ROW] = floor(pos[Y] / TILE_SIZE);
	minimap[COL] = floor(pos[X] / TILE_SIZE);
	if (minimap[X] >= map->total_column || minimap[Y] >= map->total_row)
		return (FALSE);
	if (map->row[minimap[ROW]][minimap[COL]] == '2')
		return (TRUE);
	return (FALSE);
}

int		is_tile_free(float *pos, t_settings *set, t_map *map, int secret_door)
{
	int minimap[2];

	if (pos[X] < 0 || pos[X] >= set->world[WIDTH] || pos[Y] < 0 || pos[Y] >= set->world[HEIGHT])
		return (FALSE);
	minimap[ROW] = floor(pos[Y] / TILE_SIZE);
	minimap[COL] = floor(pos[X] / TILE_SIZE);
	if (minimap[X] >= map->total_column || minimap[Y] >= map->total_row)
		return (FALSE);
	if (map->row[minimap[ROW]][minimap[COL]] == '0')
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == '3' && (secret_door))
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == '2')
		return (TRUE);
	return (FALSE);
}

float	calc_distance(int *pos, float *hit)
{
	return (sqrt(((hit[X] - pos[X]) * (hit[X] - pos[X])) + ((hit[Y] - pos[Y]) * (hit[Y] - pos[Y]))));
}

int	is_inside_world_limits(float *coord, int *world)
{
	if (coord[X] >= 0 && coord[X] <= world[WIDTH] && coord[Y] >= 0
		&& coord[Y] <= world[HEIGHT])
		return (1);
	return (0);
}

int	is_inside_screen(int *screen, float x, float y)
{
	if (x > 0 && x < screen[WIDTH] && y > 0 && y < screen[HEIGHT])
		return (TRUE);
	return (FALSE);
}