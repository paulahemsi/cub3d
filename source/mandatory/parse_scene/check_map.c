/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:50:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 21:13:32 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

static void	check_edges_content(t_cub *cub, char cell)
{	
	if ((cell == ' ') || (cell == '1'))
		return ;
	else
		return_error(cub, -107);
}

static int	check_if_is(int check, int row, int col, t_map *map)
{
	if (check == VALID_CELL)
	{
		if (row < 0 || row > (map->total_row - 1)
			|| col < 0 || col > (map->total_column - 1))
			return (0);
		return (1);
	}
	if (check == EDGE)
	{
		if ((row == 0) || (col == 0)
			|| (row == (map->total_row - 1))
			|| (col == (map->total_column - 1)))
			return (TRUE);
		return (FALSE);
	}
	return (0);
}

static void	check_neighbors(char **map, int row, int col, t_cub *cub)
{
	int		col_offset;
	int		row_offset;
	t_map	*game_map;

	game_map = &cub->game.map;
	row_offset = -1;
	while (row_offset <= 1)
	{
		col_offset = -1;
		while (col_offset <= 1)
		{
			if (check_if_is(VALID_CELL, (row + row_offset),
					(col + col_offset), game_map))
			{
				if (!(map[row + row_offset][col + col_offset] == ' ')
				&& !(map[row + row_offset][col + col_offset] == '1'))
					return_error(cub, -107);
			}
			col_offset++;
		}
		row_offset++;
	}
}

static void	store_player_settings(t_player *player, char *dir, int row, int col)
{
	if (ft_strchr("NS", *dir))
	{
		if (*dir == 'N')
			player->angle = 3 * PI / 2;
		else
			player->angle = PI / 2;
	}
	else
	{
		if (*dir == 'W')
			player->angle = PI;
		else
			player->angle = 2 * PI;
	}
	player->pos[X] = col * TILE_SIZE;
	player->pos[Y] = row * TILE_SIZE;
	player->speed = 10;
	player->rotate_speed = 2.5 * (PI / 180);
	*dir = '0';
}

void	check_map(t_cub *cub, t_render *game)
{
	char	**map;
	int		row;
	int		col;

	row = -1;
	map = game->map.row;
	while (map[++row])
	{
		col = -1;
		while (map[row][++col])
		{
			if (check_if_is(EDGE, row, col, &game->map))
				check_edges_content(cub, map[row][col]);
			if (map[row][col] == ' ')
				check_neighbors(map, row, col, cub);
			else if (ft_strchr("NSWE", map[row][col]))
				store_player_settings(&game->player, &map[row][col], row, col);
			else if (map[row][col] == '2')
				game->num_sprites++;
		}
	}	
	if (!(game->player.angle))
		return_error(cub, -108);
}
