/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:50:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/21 02:03:12 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	check_edges(char cell)
{	
	if ((cell == ' ') || (cell == '1'))
		return ;
	else
		return_error(-7);
}

static int	is_valid_cell(int row, int col, t_map *game_map)
{
	if (row < 0 || row > (game_map->total_row - 1)
		|| col < 0 || col > (game_map->total_column - 1))
		return (0);
	return (1);
}

static void	check_neighbors(char **map, int row, int col, t_map *game_map)
{
	int	col_offset;
	int	row_offset;

	row_offset = -1;
	while (row_offset <= 1)
	{
		col_offset = -1;
		while (col_offset <= 1)
		{
			if (is_valid_cell((row + row_offset), (col + col_offset), game_map))
			{
				if (!(map[row + row_offset][col + col_offset] == ' ')
				&& !(map[row + row_offset][col + col_offset] == '1'))
					return_error(-7);
			}
			col_offset++;
		}
		row_offset++;
	}
}

static void	store_player_pos(t_player *player, char *dir, int row, int col)
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
	player->speed = 7;
	player->rotate_speed = 1.5 * (PI / 180);
	*dir = '0';
	player->height = PLAYER_HEIGHT;
	//configs->player.invisible = -1;
}

static void save_sprites_locations(t_render *game)
{
	char	**map;
	int		row;
	int		col;
	int		i;

	row = 0;
	i = 0;
	map = game->map.row;
	game->sprites = (t_sprite *)malloc(game->num_sprites * sizeof(t_sprite));
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == '2')
			{
				printf("sprite %i em (%i, %i)\n", i, row, col);
				game->sprites[i].pos[X] = col * TILE_SIZE;
				game->sprites[i].pos[Y] = row * TILE_SIZE;
				i++;
			}
			col++;
		}
		row++;
	}
}

void	check_map(t_render *game)
{
	char	**map;
	int		row;
	int		col;

	row = 0;
	map = game->map.row;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if ((row == 0) || (col == 0)
				|| (row == (game->map.total_row - 1))
				|| (col == (game->map.total_column - 1)))
				check_edges(map[row][col]);
			if (map[row][col] == ' ')
				check_neighbors(map, row, col, &game->map);
			else if (ft_strchr("NSWE", map[row][col]))
				store_player_pos(&game->player, &map[row][col], row, col);
			else if (map[row][col] == '2')
				game->num_sprites++;
			col++;
		}
		row++;
	}	
	if (!(game->player.angle))
		return_error(-7);
	save_sprites_locations(game);
	//configs->map.scale = ((configs->world_width * configs->world_height) / (configs->screen_width * configs->screen_height)) * SCALE;
}
