/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:48:42 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/08 19:04:43 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

void	parse_map_size(t_map *map, char *line)
{
	int	line_size;

	line_size = ft_strlen(line);
	if (line_size > map->total_column)
		map->total_column = line_size;
	map->total_row++;
}

static int	is_valid_char(char c, int *player)
{
	if (ft_strchr("0123456789rgbs NSEW", c))
	{
		if (ft_isupper(c))
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
	int		col;
	t_map	*map;

	map = &cub->game.map;
	col = map->total_column;
	map->row[index] = (char *)malloc((col + 1) * sizeof(char));
	map->row[index][col] = '\0';
	col = 0;
	while (line[col] != '\0')
	{
		if (!(is_valid_char(line[col], player)))
		{
			free(map->row[index]);
			map->row[index] = NULL;
			return_error(cub, -106);
		}
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
	int				fd;
	int				player;
	int				row;

	player = FALSE;
	cub->game.map.row = (char **)malloc((total_rows + 1) * sizeof(char *));
	cub->game.map.row[total_rows] = NULL;
	row = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return_error(cub, -104);
	while (get_next_line(fd, &cub->settings.line))
	{
		if (((*cub->settings.line == '1') || (*cub->settings.line == ' ')))
		{
			fill_row(cub, cub->settings.line, row, &player);
			row++;
		}
		ft_free_and_null((void **)&cub->settings.line);
	}
	if (((*cub->settings.line == '1') || (*cub->settings.line == ' ')))
		fill_row(cub, cub->settings.line, row, &player);
	ft_free_and_null((void **)&cub->settings.line);
	close(fd);
}
