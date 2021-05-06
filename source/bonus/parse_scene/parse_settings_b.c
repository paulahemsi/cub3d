/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 00:48:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/06 23:01:19 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

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

static void	parse_level(t_cub *cub, t_settings *settings, char *line)
{
	unsigned int	number;

	while (*line)
	{
		number = 0;
		while (ft_isblank(*line))
			line++;
		while (ft_isdigit(*line))
		{
			if ((settings->level))
				return_error(cub, -117);
			number = (number * 10) + (*line - '0');
			line++;
		}
		if ((number == 1) || (number == 2))
			settings->level = number;
		else if ((*line))
			return_error(cub, -117);
	}
}

static int	is_configs_set(t_settings *settings)
{
	if ((settings->floor.blue == -1) || (settings->ceiling.blue == -1))
		return (0);
	if (!(settings->level))
		return (0);
	if (!(settings->path[NORTH]) || !(settings->path[SOUTH]))
		return (0);
	if (!(settings->path[EAST]) || !(settings->path[WEST]))
		return (0);
	return (1);
}

void	parse_settings(t_cub *cub, char *line)
{
	t_settings	*settings;

	settings = &cub->settings;
	if ((ft_strnequ(line, "NO ", 3)) || (ft_strnequ(line, "NO\t", 3)))
		parse_path(cub, &settings->path[NORTH], (line + 3));
	else if ((ft_strnequ(line, "SO ", 3)) || (ft_strnequ(line, "SO\t", 3)))
		parse_path(cub, &settings->path[SOUTH], (line + 3));
	else if ((ft_strnequ(line, "WE ", 3)) || (ft_strnequ(line, "WE\t", 3)))
		parse_path(cub, &settings->path[WEST], (line + 3));
	else if ((ft_strnequ(line, "EA ", 3)) || (ft_strnequ(line, "EA\t", 3)))
		parse_path(cub, &settings->path[EAST], (line + 3));
	else if ((ft_strnequ(line, "F ", 2)) || (ft_strnequ(line, "F\t", 2)))
		parse_colors(cub, &settings->floor, (line + 2));
	else if ((ft_strnequ(line, "C ", 2)) || (ft_strnequ(line, "C\t", 2)))
		parse_colors(cub, &settings->ceiling, (line + 2));
	else if ((ft_strnequ(line, "L ", 2)) || (ft_strnequ(line, "L\t", 2)))
		parse_level(cub, settings, (line + 2));
	else if ((*line == '1' || (*line == ' ')) && ((is_configs_set(settings))))
		parse_map_size(&cub->game.map, line);
	else if (*line != '\0')
		return_error(cub, -116);
}
