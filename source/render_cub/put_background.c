/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:08:57 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/10 21:35:04 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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

static int	put_surface(t_data *img, t_gradient *gradient, int *line, t_rgb *surface)
{
	int init[2];

	init[X] = 0;
	init[Y] = *line;
	if (img->cub->gradient == TRUE)
		activate_gradient(&img->c, surface, gradient);
	else
		define_img_colors(img, surface->red, surface->green, surface->blue);
	put_line(img, init, img->cub->screen_width, *line);
	return (*line += 1);
}

static void	toggle_increment(t_gradient *gradient)
{
	gradient->increment.red *= TOGGLE;
	gradient->increment.green *= TOGGLE;
	gradient->increment.blue *= TOGGLE;
}

void	put_background(t_data *img, t_configs *cub)
{
	int line;
	float increment;
	t_gradient	gradient;

	increment = 1;
	line = 0;
	define_img_colors(img, cub->ceiling.red, cub->ceiling.green, cub->ceiling.blue);
	define_gradient(&cub->ceiling, &cub->floor, &gradient);
	while (line < (cub->screen_height / 2))
		line = put_surface(img, &gradient, &line, &cub->floor);
	toggle_increment(&gradient);
	define_img_colors(img, cub->floor.red, cub->floor.green, cub->floor.blue);
	while (line < cub->screen_height)
		line = put_surface(img, &gradient, &line, &cub->ceiling);
}
