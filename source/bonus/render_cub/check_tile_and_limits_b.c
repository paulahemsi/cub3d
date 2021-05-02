/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tile_and_limits_b.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:15:51 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/02 17:41:23 by phemsi-a         ###   ########.fr       */
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
	return (FALSE);
}

static void	grab_item(t_cub *cub, int id)
{
	//int i;

	cub->game.hud_id++;
	//printf("hud_id %i\n", cub->game.hud_id);
	
	printf("id %i\n", id);
	//printf("before index: %i active: %i \n", (id - 2), cub->game.sprites[id - 2].active);
	cub->game.sprites[id - 2].active = FALSE;
	//printf("after index: %i active: %i \n", (id - 2), cub->game.sprites[id - 2].active);
	
	// if (cub->game.sprites)
	// {
	// 	i = 0;
	// 	while (i < cub->game.num_sprites)
	// 	{
	// 		if (cub->game.sprites[i].texture.img.ptr)
	// 			mlx_destroy_image(cub->mlx_ptr, cub->game.sprites[i].texture.img.ptr);
	// 		i++;
	// 	}
	// 	free(cub->game.sprites);
	// }
	// cub->game.num_sprites--;
	// save_sprites_locations(&cub->game);
}

int	is_tile_free(float *pos, t_cub *cub, t_map *map, int secret_door)
{
	int			minimap[2];
	t_settings	*set;
	int 		sprite_id;

	set = &cub->settings;
	if (!(is_inside_world_limits(pos, set->world)))
		return (FALSE);
	minimap[ROW] = floor(pos[Y] / TILE_SIZE);
	minimap[COL] = floor(pos[X] / TILE_SIZE);
	if (minimap[X] >= map->total_column || minimap[Y] >= map->total_row)
		return (FALSE);
	if (map->row[minimap[ROW]][minimap[COL]] == '0')
		return (TRUE);
	else
	{
		ft_printf("tile content: %c\n", map->row[minimap[ROW]][minimap[COL]]);

	}
	if (map->row[minimap[ROW]][minimap[COL]] == '9' && (secret_door))
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] >= '2' && map->row[minimap[ROW]][minimap[COL]] <= '6')//!mudar para id?
	{
		sprite_id = map->row[minimap[ROW]][minimap[COL]] - '0';
		grab_item(cub, sprite_id);
		map->row[minimap[ROW]][minimap[COL]] = '0';
		return (FALSE);
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
