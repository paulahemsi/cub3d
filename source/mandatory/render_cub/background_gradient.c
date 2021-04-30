/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_gradient.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:20:05 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 21:13:52 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

void	activate_gradient(t_rgb *color, t_rgb *opposite_surface,
		t_gradient *gradient)
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

void	define_gradient(t_rgb *ceil, t_rgb *floor, t_gradient *gradient)
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

void	toggle_increment(t_gradient *gradient)
{
	gradient->increment.red *= TOGGLE;
	gradient->increment.green *= TOGGLE;
	gradient->increment.blue *= TOGGLE;
}
