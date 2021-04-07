/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:08:57 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/07 00:09:04 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	check_colors(t_rgb *color)
{
	if (color->red > 255 || color->blue > 255 || color->green > 255)
		return_error(-5);
}

void	put_background(t_data *img)
{
	int line;
	int init[2];
	float increment;

	increment = 1;
	check_colors(&img->cub->ceiling);
	check_colors(&img->cub->floor);
	line = 0;
	init[X] = 0;
	define_img_colors(img, img->cub->ceiling.red, img->cub->ceiling.green, img->cub->ceiling.blue);
	while (line < (img->cub->height / 2))
	{
		init[Y] = line;
		put_line(img, init, img->cub->width, line);
		line++;
		if (img->c.red < 255)
			img->c.red += ceil(increment);	
	}
	define_img_colors(img, img->cub->floor.red, img->cub->floor.green, img->cub->floor.blue);
	while (line < img->cub->height)
	{
		init[Y] = line;
		put_line(img, init, img->cub->width, line);
		line++;
		if (img->c.red > 0)
			img->c.red -= ceil(increment);
	}
}
