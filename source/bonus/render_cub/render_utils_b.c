/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:01:20 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/07 03:49:36 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

float	hit_distance(int *pos, float *hit)
{
	return (sqrt(((hit[X] - pos[X]) * (hit[X] - pos[X]))
			+ ((hit[Y] - pos[Y]) * (hit[Y] - pos[Y]))));
}

float	define_distance(int *pos1, int *pos2)
{
	return (sqrt(((pos2[X] - pos1[X]) * (pos2[X] - pos1[X]))
			+ ((pos2[Y] - pos1[Y]) * (pos2[Y] - pos1[Y]))));
}

int	is_ray_facing(int direction, float angle)
{
	if (direction == DOWN)
		return (angle > 0 && angle < PI);
	else if (direction == RIGHT)
		return (angle < PI / 2 || angle > 1.5 * PI);
	else if (direction == UP)
		return (!(angle > 0 && angle < PI));
	else if (direction == LEFT)
		return (!(angle < PI / 2 || angle > 1.5 * PI));
	else
		return (ERROR);
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
