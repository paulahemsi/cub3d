/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:50:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/10 13:33:04 by phemsi-a         ###   ########.fr       */
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

static int	is_valid_cell(int row, int col, t_configs *configs)
{
	if (row < 0 || row > (configs->map.total_row - 1) ||
		col < 0 || col > (configs->map.total_column - 1))
		return (0);
	return (1);
}

static void	check_neighbors(char **map, int row, int col, t_configs *configs)
{
	int col_offset;
	int row_offset;

	row_offset = -1;
	while (row_offset <= 1)
	{
		col_offset = -1;
		while (col_offset <= 1)
		{
			if (is_valid_cell((row + row_offset), (col + col_offset), configs))
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

static void	store_player_pos(t_configs *configs, char *dir, int row, int col)
{
	if (ft_strchr("NS", *dir))
	{
		if (*dir == 'N')
			configs->player.angle = 3 * PI / 2;
		else
			configs->player.angle = PI / 2;
	}
	else
	{
		if (*dir == 'W')
			configs->player.angle = PI;
		else
			configs->player.angle = 2 * PI;
	}
	configs->player.pos[X] = col * TILE_SIZE;
	configs->player.pos[Y] = row * TILE_SIZE;
	configs->player.speed = 5;
	configs->player.rotate_speed = 2 * (PI / 180);
	*dir = '0';
	configs->player.height = PLAYER_HEIGHT;
	//configs->player.invisible = -1;
	configs->player.plane_dist = floor((configs->screen_width / 2) / tan(HALF_FOV));
	configs->ray.step= FOV / configs->screen_width;
	configs->ray.total = configs->screen_width;
}

void		check_map(t_configs *configs)
{
	char	**map;
	int		row;
	int		col;

	row = 0;
	map = configs->map.row;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if ((row == 0) || (col == 0)
				|| (row == (configs->map.total_row - 1))
				|| (col == (configs->map.total_column - 1)))
				check_edges(map[row][col]);
			if (map[row][col] == ' ')
				check_neighbors(map, row, col, configs);
			else if (ft_strchr("NSWE", map[row][col]))
				store_player_pos(configs, &map[row][col], row, col);
			col++;
		}
		row++;
	}	
	if (!(configs->player.angle))
		return_error(-7);
	//configs->map.scale = ((configs->world_width * configs->world_height) / (configs->screen_width * configs->screen_height)) * SCALE;
}
