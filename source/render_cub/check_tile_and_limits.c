/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tile_and_limits.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:15:51 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 19:55:26 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	has_wall(float *pos, t_settings *set, t_map *map)
{
	int	minimap[2];

	if (!(is_inside_world_limits(pos, set->world)))
		return (FALSE);
	minimap[ROW] = floor(pos[Y] / TILE_SIZE);
	minimap[COL] = floor(pos[X] / TILE_SIZE);
	if (minimap[X] >= map->total_column || minimap[Y] >= map->total_row)
		return (FALSE);
	if (map->row[minimap[ROW]][minimap[COL]] == '3')
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == '1')
		return (TRUE);
	return (FALSE);
}

int	is_tile_free(float *pos, t_settings *set, t_map *map, int secret_door)
{
	int	minimap[2];

	if (!(is_inside_world_limits(pos, set->world)))
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
		return (FALSE);
	return (FALSE);
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
