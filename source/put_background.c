/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:08:57 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/03 17:55:50 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	check_colors(t_rgb *color)
{
	if (color->red > 255 || color->blue > 255 || color->green > 255)
		return_error(-5);
}

void	put_background(t_data *img)
{
	int line;
	int init[2];

	check_colors(&img->cub->ceiling);
	check_colors(&img->cub->floor);
	line = 0;
	init[X] = 0;
	img->c.red = img->cub->ceiling.red;
	img->c.green = img->cub->ceiling.green;
	img->c.blue = img->cub->ceiling.blue;
	while (line < (img->cub->height / 2))
	{
		init[Y] = line;
		ft_printf("\n");
		put_line(img, init, img->cub->width, line);
		line++;
		if (img->c.red > 0)
			img->c.red--;
	}
	img->c.red = img->cub->floor.red;
	img->c.green = img->cub->floor.green;
	img->c.blue = img->cub->floor.blue;
	line = img->cub->height;
	while (line > ((img->cub->height / 2) - 1))
	{
		init[Y] = line;
		ft_printf("oi\n");
		put_line(img, init, img->cub->width, line);
		line--;
		if (img->c.red > 0)
			img->c.red--;
	}
}
