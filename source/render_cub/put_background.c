/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:08:57 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/10 17:45:16 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"


void	put_background(t_data *img)
{
	int line;
	int init[2];
	float increment;

	increment = 1;
	line = 0;
	init[X] = 0;
	define_img_colors(img, img->cub->ceiling.red, img->cub->ceiling.green, img->cub->ceiling.blue);
	while (line < (img->cub->screen_height / 2))
	{
		init[Y] = line;
		put_line(img, init, img->cub->screen_width, line);
		line++;
		if (img->cub->gradient == TRUE)
		{
			if (img->c.red < 255)
				img->c.red += ceil(increment);
		}
		else
			img->c.red = img->cub->ceiling.red;
	}
	define_img_colors(img, img->cub->floor.red, img->cub->floor.green, img->cub->floor.blue);
	while (line < img->cub->screen_height)
	{
		init[Y] = line;
		put_line(img, init, img->cub->screen_width, line);
		line++;
		if (img->cub->gradient == TRUE)
		{
			if (img->c.red > 0)
				img->c.red -= ceil(increment);
		}
		else
			img->c.red = img->cub->floor.red;
	}
}
