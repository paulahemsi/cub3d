/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 00:48:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/23 11:13:51 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

static void	parse_path(char **texture_path, char *line)
{
	if (*texture_path)
		return_error(-5);
	if (!(*texture_path = ft_strtrim(line, " \t")))
		return_error(-6);
}

static void	parse_colors(t_rgb *direction, char *line)
{
	unsigned int	number;

	while (*line)
	{
		number = 0;
		while (ft_isblank(*line))
			line++;
		while (ft_isdigit(*line))
		{
			if (direction->blue >= 0)
				return_error(-5);
			number = (number * 10) + (*line - '0');
			line++;
		}
		if (direction->red < 0)
			direction->red = number;
		else if (direction->green < 0)
			direction->green = number;
		else if (direction->blue < 0)
			direction->blue = number;
		else if ((*line))
			return_error(-5);
		if ((*line == ',') && (direction->blue < 0))
			line++;
	}
}

static void	parse_resolution(t_configs *configs, char *line)
{
	unsigned int	number;

	while (*line)
	{
		number = 0;
		while (ft_isblank(*line))
			line++;
		while (ft_isdigit(*line))
		{
			if ((configs->window_width) && (configs->window_height))
				return_error(-5);
			number = (number * 10) + (*line - '0');
			line++;
		}
		if (!(configs->window_width) && (number))
			configs->window_width = number;
		else if (!(configs->window_height) && (number))
			configs->window_height = number;
		else if ((*line))
			return_error(-5);
	}
}

static int	all_configs(t_configs *configs)
{
	if ((configs->floor.blue == -1) || (configs->ceiling.blue == -1))
		return (0);
	if (!(configs->window_width) || !(configs->window_height))
		return (0);
	if (!(configs->path.north) || !(configs->path.south))
		return (0);
	if (!(configs->path.east) || !(configs->path.west))
		return (0);
	if (!(configs->path.sprite))
		return (0);
	return (1);
}

void		parse_configs(t_configs *configs, char *line)
{
	if ((ft_strnequ(line, "NO ", 3)) || (ft_strnequ(line, "NO\t", 3)))
		parse_path(&configs->path.north, (line + 3));
	else if ((ft_strnequ(line, "SO ", 3)) || (ft_strnequ(line, "SO\t", 3)))
		parse_path(&configs->path.south, (line + 3));
	else if ((ft_strnequ(line, "WE ", 3)) || (ft_strnequ(line, "WE\t", 3)))
		parse_path(&configs->path.west, (line + 3));
	else if ((ft_strnequ(line, "EA ", 3)) || (ft_strnequ(line, "EA\t", 3)))
		parse_path(&configs->path.east, (line + 3));
	else if ((ft_strnequ(line, "S ", 2)) || (ft_strnequ(line, "S\t", 2)))
		parse_path(&configs->path.sprite, (line + 2));
	else if ((ft_strnequ(line, "F ", 2)) || (ft_strnequ(line, "F\t", 2)))
		parse_colors(&configs->floor, (line + 2));
	else if ((ft_strnequ(line, "C ", 2)) || (ft_strnequ(line, "C\t", 2)))
		parse_colors(&configs->ceiling, (line + 2));
	else if ((ft_strnequ(line, "R ", 2)) || (ft_strnequ(line, "R\t", 2)))
		parse_resolution(configs, (line + 2));
	else if (((*line == '1') || (*line == ' ')) && ((all_configs(configs))))
		set_map(configs, line);
	else if (*line != '\0')
		return_error(-5);
}
