/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:50:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/23 19:25:11 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

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

void		check_walls(t_configs *configs)
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
				|| (row == (configs->map.total_row -1)) 
				|| (col == (configs->map.total_column -1)))
				check_edges(map[row][col]);
			if (map[row][col] == ' ')
				check_neighbors(map, row, col, configs);
			col++;
		}
		row++;
	}
}