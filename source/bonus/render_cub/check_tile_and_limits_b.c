/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tile_and_limits_b.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:15:51 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/03 20:16:48 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

int	has_wall(float *pos, t_settings *set, t_map *map)
{
	int	minimap[2];

	if (!(is_inside_world_limits(pos, set->world)))
		return (FALSE);
	minimap[ROW] = floor(pos[Y] / TILE_SIZE);
	minimap[COL] = floor(pos[X] / TILE_SIZE);
	if (minimap[X] >= map->total_column || minimap[Y] >= map->total_row)
		return (FALSE);
	if (map->row[minimap[ROW]][minimap[COL]] == '9')
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == '1')
		return (TRUE);
	if (ft_isalpha(map->row[minimap[ROW]][minimap[COL]]))
		return (TRUE);
	return (FALSE);
}

static void	grab_item(t_cub *cub, t_map *map, int row, int col)
{
	int 		id;

	id = map->row[row][col] - '0';
	cub->game.sprites[id - 2].active = FALSE;
	map->row[row][col] = '0';
	if (id == 2)
		cub->game.item.red_key = TRUE;
	else if (id == 3)
		cub->game.item.green_key = TRUE;
	else if (id == 4)
		cub->game.item.blue_key = TRUE;
	else if (id == 5)
		cub->game.item.map = TRUE;
	else if (id == 6)
		cub->game.item.glasses = TRUE;
}

int	is_tile_free(float *pos, t_cub *cub, t_map *map, int secret_door)
{
	int			minimap[2];
	t_settings	*set;

	set = &cub->settings;
	if (!(is_inside_world_limits(pos, set->world)))
		return (FALSE);
	minimap[ROW] = floor(pos[Y] / TILE_SIZE);
	minimap[COL] = floor(pos[X] / TILE_SIZE);
	if (minimap[X] >= map->total_column || minimap[Y] >= map->total_row)
		return (FALSE);
	if (map->row[minimap[ROW]][minimap[COL]] == '0')
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == '9' && (secret_door))
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == 'r' && (cub->game.item.red_key))
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == 'g' && (cub->game.item.green_key))
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == 'b' && (cub->game.item.blue_key))
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] >= '2'
		&& map->row[minimap[ROW]][minimap[COL]] <= '6')
	{
		grab_item(cub, map, minimap[ROW], minimap[COL]);
		return (TRUE);
	}
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
