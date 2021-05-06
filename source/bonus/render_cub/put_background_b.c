/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:08:57 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/06 00:49:42 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static int	put_surface(t_cub *cub, t_gradient *gradient,
		int *line, t_rgb *surface)
{
	int	init[2];

	init[X] = 0;
	init[Y] = *line;
	if (cub->toggle.gradient == TRUE)
		activate_gradient(&cub->game.color, surface, gradient);
	else if ((cub->toggle.night_mode == -1) && (cub->game.win))
		define_img_colors(&cub->game.color, surface->red,
			surface->green, surface->blue);
	if (cub->toggle.debug == TRUE)
		define_img_colors(&cub->game.color, 60, 21, 79);
	put_line(cub, init, cub->settings.screen[WIDTH], *line);
	return (*line += 1);
}

void	put_background(t_cub *cub, t_rgb *ceiling, t_rgb *floor, t_rgb *color)
{
	int			line;
	float		increment;
	t_gradient	gradient;
	t_rgb		night_vision[2];

	increment = 1;
	line = 0;
	define_img_colors(color, 0, 0, 0);
	if (cub->game.win)
	{
		cub->toggle.gradient *= TOGGLE;
		define_img_colors(color, ceiling->red, ceiling->green, ceiling->blue);
	}
	if (cub->toggle.night_mode == TRUE)
		init_night_vision(cub, night_vision, &gradient);
	else if (cub->toggle.gradient == TRUE)
		define_gradient(ceiling, floor, &gradient);
	while (line < (cub->settings.screen[HEIGHT] / 2))
		line = put_surface(cub, &gradient, &line, floor);
	toggle_increment(&gradient);
	define_img_colors(color, 255, 255, 255);
	if (cub->toggle.night_mode == TRUE)
		night_vision_floor(cub, night_vision);
	else if (cub->game.win)
		define_img_colors(color, floor->red, floor->green, floor->blue);
	while (line < cub->settings.screen[HEIGHT])
		line = put_surface(cub, &gradient, &line, ceiling);
}
