/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:01:20 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/12 16:28:26 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

float	degrees_to_radians(int degree)
{
	return ((float)degree * PI / 180);
}

int		radiands_to_degrees(float radian)
{
	return (floor(radian * 180 / PI));
}

void	define_img_colors(t_data *img, int red, int green, int blue)
{
	img->c.red = red;
	img->c.green = green;
	img->c.blue = blue;
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

int		is_tile_free(float *pos, t_configs *cub, int secret_door)
{
	int minimap[2];

	if (pos[X] < 0 || pos[X] >= cub->world_width || pos[Y] < 0 || pos[Y] >= cub->world_height)
		return (FALSE);
	minimap[ROW] = floor(pos[Y] / TILE_SIZE);
	minimap[COL] = floor(pos[X] / TILE_SIZE);
	if (minimap[X] >= cub->map.total_column || minimap[Y] >= cub->map.total_row)
		return (FALSE);
	if (cub->map.row[minimap[ROW]][minimap[COL]] == '0')
		return (TRUE);
	if (cub->map.row[minimap[ROW]][minimap[COL]] == '3' && (secret_door))
		return (TRUE);
	return (FALSE);
}

float	calc_distance(int *pos, float *hit)
{
	return (sqrt(((hit[X] - pos[X]) * (hit[X] - pos[X])) + ((hit[Y] - pos[Y]) * (hit[Y] - pos[Y]))));
}