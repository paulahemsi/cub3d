/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:48:42 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/23 16:50:18 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void		set_map(t_configs *configs, char *line)
{
	unsigned int	line_size;

	line_size = ft_strlen(line);
	if (line_size > configs->map.total_column)
		configs->map.total_column = line_size;
	configs->map.total_row++;
}

static int is_valid_char(char c, int *player)
{
	if (ft_strchr("012 NSEW", c))
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

static void	fill_row(t_configs *configs, char *line, int	index, int *player)
{
	unsigned int	col;

	col = configs->map.total_column;
	configs->map.row[index] = (char *)malloc((col + 1) * sizeof(char));
	configs->map.row[index][col] = '\0';
	col = 0;
	while (line[col] != '\0')
	{
		if (!(is_valid_char(line[col], player)))
			return_error(-7);
		configs->map.row[index][col] = line[col];
		col++;
	}
	while (col < configs->map.total_column)
	{
		configs->map.row[index][col] = ' ';
		col++;
	}
}

void		fill_map(t_configs *configs, char *file)
{
	char			*line;
	int				row;
	int				fd;
	int				player;

	player = FALSE;
	row = configs->map.total_row;
	configs->map.row = (char **)malloc((row + 1) * sizeof(char *));
	configs->map.row[row] = NULL;
	row = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return_error(-2);
	while (get_next_line(fd, &line))
	{
		if (((*line == '1') || (*line == ' ')))
		{
			fill_row(configs, line, row, &player);
			row++;
		}
		free(line);
	}
	fill_row(configs, line, row, &player);
	free(line);
	close(fd);
}
