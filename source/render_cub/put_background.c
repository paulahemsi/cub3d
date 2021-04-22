/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:08:57 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/22 20:56:47 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

//!Vale a pena dar uma reorganizada

static void	activate_gradient(t_rgb *color, t_rgb *opposite_surface, t_gradient *gradient)
{
	if (gradient->increment.red > 0)
	{
		if (color->red < opposite_surface->red)
			color->red += gradient->increment.red;
	}
	else
		if (color->red > opposite_surface->red)
			color->red += gradient->increment.red;
	if (gradient->increment.green > 0)
	{
		if (color->green < opposite_surface->green)
			color->green += gradient->increment.green;
	}
	else
		if (color->green > opposite_surface->green)
			color->green += gradient->increment.green;
	if (gradient->increment.blue > 0)
	{
		if (color->blue < opposite_surface->blue)
			color->blue += gradient->increment.blue;
	}
	else
		if (color->blue > opposite_surface->blue)
			color->blue += gradient->increment.blue;
}

static void	define_gradient(t_rgb *ceil, t_rgb *floor, t_gradient *gradient)
{
	gradient->increment.red = 1;
	gradient->increment.green = 1;
	gradient->increment.blue = 1;
	gradient->color_distance.red = ceil->red - floor->red;
		if (gradient->color_distance.red > 0)
			gradient->increment.red *= TOGGLE;
	gradient->color_distance.green = ceil->green - floor->green;
		if (gradient->color_distance.green > 0)
			gradient->increment.green *= TOGGLE;
	gradient->color_distance.blue = ceil->blue - floor->blue;
		if (gradient->color_distance.blue > 0)
			gradient->increment.blue *= TOGGLE;
}

static int	put_surface(t_cub *cub, t_gradient *gradient, int *line, t_rgb *surface)
{
	int init[2];

	init[X] = 0;
	init[Y] = *line;
	if (cub->toggle.gradient == TRUE)
		activate_gradient(&cub->game.color, surface, gradient);
	else if (cub->toggle.night_mode == -1)
		define_img_colors(&cub->game.color, surface->red, surface->green, surface->blue);
	if (cub->toggle.debug == TRUE)
		define_img_colors(&cub->game.color, 60, 21, 79);
	put_line(cub, init, cub->settings.screen[WIDTH], *line);
	return (*line += 1);
}

static void	toggle_increment(t_gradient *gradient)
{
	gradient->increment.red *= TOGGLE;
	gradient->increment.green *= TOGGLE;
	gradient->increment.blue *= TOGGLE;
}

static void	define_night_vision(t_rgb *night_vision)
{
	night_vision[CEILING].red = 0;
	night_vision[CEILING].green = 116;
	night_vision[CEILING].blue = 0;
	night_vision[FLOOR].red = 1;
	night_vision[FLOOR].green = 7;
	night_vision[FLOOR].blue = 1;
}

void	put_background(t_cub *cub)
{
	int line;
	float increment;
	t_gradient	gradient;
	t_rgb		night_vision[2];

	increment = 1;
	line = 0;
	define_img_colors(&cub->game.color,
						cub->settings.ceiling.red,
						cub->settings.ceiling.green,
						cub->settings.ceiling.blue);
	if (cub->toggle.night_mode == TRUE)
	{
		define_night_vision(night_vision);
		define_img_colors(&cub->game.color,
							night_vision[CEILING].red,
							night_vision[CEILING].green,
							night_vision[CEILING].blue);
		define_gradient(&night_vision[CEILING], &night_vision[FLOOR], &gradient);
	}
	else
		define_gradient(&cub->settings.ceiling, &cub->settings.floor, &gradient);
	while (line < (cub->settings.screen[HEIGHT] / 2))
		line = put_surface(cub, &gradient, &line, &cub->settings.floor);
	toggle_increment(&gradient);
	if (cub->toggle.night_mode == TRUE)
		define_img_colors(&cub->game.color,
							night_vision[FLOOR].red,
							night_vision[FLOOR].green,
							night_vision[FLOOR].blue);
	else
		define_img_colors(&cub->game.color, cub->settings.floor.red, cub->settings.floor.green, cub->settings.floor.blue);
	while (line < cub->settings.screen[HEIGHT])
		line = put_surface(cub, &gradient, &line, &cub->settings.ceiling);
}
