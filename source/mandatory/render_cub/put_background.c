/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:08:57 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/01 01:08:01 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

static void	put_surface(t_cub *cub, int *line)
{
	int	init[2];

	init[X] = 0;
	init[Y] = *line;
	put_line(cub, init, cub->settings.screen[WIDTH], *line);
}

void	put_background(t_cub *cub, t_rgb *ceiling, t_rgb *floor, t_rgb *color)
{
	int			line;

	line = 0;
	define_img_colors(color, ceiling->red, ceiling->green, ceiling->blue);
	while (line < (cub->settings.screen[HEIGHT] / 2))
	{
		put_surface(cub, &line);
		line++;
	}
	define_img_colors(color, floor->red, floor->green, floor->blue);
	while (line < cub->settings.screen[HEIGHT])
	{
		put_surface(cub, &line);
		line++;
	}
}
