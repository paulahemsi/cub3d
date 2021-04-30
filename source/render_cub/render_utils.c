/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:01:20 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 15:20:38 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

float	hit_distance(int *pos, float *hit)
{
	return (sqrt(((hit[X] - pos[X]) * (hit[X] - pos[X])) + ((hit[Y] - pos[Y]) * (hit[Y] - pos[Y]))));
}

float	define_distance(int *pos1, int *pos2)
{
	return (sqrt(((pos2[X] - pos1[X]) * (pos2[X] - pos1[X])) + ((pos2[Y] - pos1[Y]) * (pos2[Y] - pos1[Y]))));
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
