/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:48:42 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/29 14:24:34 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	parse_map_size(t_map *map, char *line)
{
	unsigned int	line_size;

	line_size = ft_strlen(line);
	if (line_size > map->total_column)
		map->total_column = line_size;
	map->total_row++;
}

static int	is_valid_char(char c, int *player)
{
	if (ft_strchr("0123 NSEW", c))
	{
		if (ft_isalpha(c))
		{
			if (*player)
				return (FALSE);
			*player = TRUE;
		}
		return (TRUE);
	}
	return (FALSE);
}

static void	fill_row(t_cub *cub, char *line, int index, int *player)
{
	unsigned int	col;
	t_map			*map;

	map = &cub->game.map;
	col = map->total_column;
	map->row[index] = (char *)malloc((col + 1) * sizeof(char));
	map->row[index][col] = '\0';
	col = 0;
	while (line[col] != '\0')
	{
		if (!(is_valid_char(line[col], player)))
			return_error(cub, -7);
		map->row[index][col] = line[col];
		col++;
	}
	while (col < map->total_column)
	{
		map->row[index][col] = ' ';
		col++;
	}
}

void	fill_map(t_cub *cub, char *file, int total_rows)
{
	char			*line;
	int				fd;
	int				player;
	int				row;

	player = FALSE;
	cub->game.map.row = (char **)malloc((total_rows + 1) * sizeof(char *));
	cub->game.map.row[total_rows] = NULL;
	row = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return_error(cub, -2);
	while (get_next_line(fd, &line))
	{
		if (((*line == '1') || (*line == ' ')))
		{
			fill_row(cub, line, row, &player);
			row++;
		}
		free(line);
	}
	if (((*line == '1') || (*line == ' ')))
		fill_row(cub, line, row, &player);
	free(line);
	close(fd);
}
