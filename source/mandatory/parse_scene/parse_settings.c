/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 00:48:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/09 17:20:26 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

static void	parse_path(t_cub *cub, char **texture_path, char *line)
{
	if (*texture_path)
		return_error(cub, -119);
	*texture_path = ft_strtrim(line, " \t");
	if (!(*texture_path))
		return_error(cub, -119);
}

static void	parse_colors(t_cub *cub, t_rgb *direction, char *line)
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
				return_error(cub, -118);
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
			return_error(cub, -118);
		if ((*line == ',') && (direction->blue < 0))
			line++;
	}
}

static void	parse_resolution(t_cub *cub, t_settings *settings, char *line)
{
	unsigned int	number;

	while (*line)
	{
		number = 0;
		while (ft_isblank(*line))
			line++;
		while (ft_isdigit(*line))
		{
			if ((settings->screen[WIDTH]) && (settings->screen[HEIGHT]))
				return_error(cub, -117);
			number = (number * 10) + (*line - '0');
			line++;
		}
		if (!(settings->screen[WIDTH]) && (number))
			settings->screen[WIDTH] = number;
		else if (!(settings->screen[HEIGHT]) && (number))
			settings->screen[HEIGHT] = number;
		else if ((*line))
			return_error(cub, -117);
	}
}

static int	is_configs_set(t_settings *settings)
{
	if ((settings->floor.blue == -1) || (settings->ceiling.blue == -1))
		return (0);
	if (!(settings->screen[WIDTH]) || !(settings->screen[HEIGHT]))
		return (0);
	if (!(settings->path[NORTH]) || !(settings->path[SOUTH]))
		return (0);
	if (!(settings->path[EAST]) || !(settings->path[WEST]))
		return (0);
	if (!(settings->path[SPRITE]))
		return (0);
	return (1);
}

void	parse_settings(t_cub *cub, char *line, t_settings *settings)
{
	if ((ft_strnequ(line, "NO ", 3)) || (ft_strnequ(line, "NO\t", 3)))
		parse_path(cub, &settings->path[NORTH], (line + 3));
	else if ((ft_strnequ(line, "SO ", 3)) || (ft_strnequ(line, "SO\t", 3)))
		parse_path(cub, &settings->path[SOUTH], (line + 3));
	else if ((ft_strnequ(line, "WE ", 3)) || (ft_strnequ(line, "WE\t", 3)))
		parse_path(cub, &settings->path[WEST], (line + 3));
	else if ((ft_strnequ(line, "EA ", 3)) || (ft_strnequ(line, "EA\t", 3)))
		parse_path(cub, &settings->path[EAST], (line + 3));
	else if ((ft_strnequ(line, "S ", 2)) || (ft_strnequ(line, "S\t", 2)))
		parse_path(cub, &settings->path[SPRITE], (line + 2));
	else if ((ft_strnequ(line, "F ", 2)) || (ft_strnequ(line, "F\t", 2)))
		parse_colors(cub, &settings->floor, (line + 2));
	else if ((ft_strnequ(line, "C ", 2)) || (ft_strnequ(line, "C\t", 2)))
		parse_colors(cub, &settings->ceiling, (line + 2));
	else if ((ft_strnequ(line, "R ", 2)) || (ft_strnequ(line, "R\t", 2)))
		parse_resolution(cub, settings, (line + 2));
	else if ((*line == '1' || (*line == ' ')) && ((is_configs_set(settings))))
		parse_map_size(&cub->game.map, line);
	else if (*line != '\0')
		return_error(cub, -116);
}
