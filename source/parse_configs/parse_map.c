/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:48:42 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/15 02:44:19 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void		parse_map_size(t_settings *cub, char *line)
{
	unsigned int	line_size;

	line_size = ft_strlen(line);
	if (line_size > cub->map.total_column)
		cub->map.total_column = line_size;
	cub->map.total_row++;
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

static void	fill_row(t_settings *cub, char *line, int index, int *player)
{
	unsigned int	col;

	col = cub->map.total_column;
	cub->map.row[index] = (char *)malloc((col + 1) * sizeof(char));
	cub->map.row[index][col] = '\0';
	col = 0;
	while (line[col] != '\0')
	{
		if (!(is_valid_char(line[col], player)))
			return_error(-7);
		cub->map.row[index][col] = line[col];
		col++;
	}
	while (col < cub->map.total_column)
	{
		cub->map.row[index][col] = ' ';
		col++;
	}
}

static void	define_world_size(t_settings *cub)
{
	cub->world[WIDTH] = cub->map.total_column * TILE_SIZE;
	cub->world[HEIGHT] = cub->map.total_row * TILE_SIZE;
}

void		fill_map(t_settings *cub, char *file, int row)
{
	char			*line;
	int				fd;
	int				player;

	player = FALSE;
	cub->map.row = (char **)malloc((row + 1) * sizeof(char *));
	cub->map.row[row] = NULL;
	row = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return_error(-2);
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
	define_world_size(cub);
	free(line);
	close(fd);
}
