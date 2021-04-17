/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:56:02 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/17 18:07:57 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	color_picker(unsigned char red, unsigned char green,
							unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}

void		put_pixel(t_data *img, int pos_x, int pos_y, int color)
{
	char	*dst;
	int		offset;

	offset = (pos_y * img->line_length + pos_x * (img->bits_per_pixel / 8));
	dst = img->data + offset;
	*(unsigned int*)dst = color;
}

// void		put_square(t_data *img, int pos_x, int pos_y, int color)
// {
// 	int x_init;

// 	x_init = pos_x;
// 	while (pos_y < img->cub->height)
// 	{
// 		while (pos_x < img->cub->width)
// 		{
// 			put_pixel(img, pos_x, pos_y, color);
// 			pos_x++;
// 		}
// 		pos_y++;
// 		pos_x = x_init;
// 	}
// }

void	put_circle(t_data *img, int center_x, int center_y, int radius)
{
	int radius_squared;
	int x;
	int y;

	radius_squared = pow(radius, 2);
	x = center_x - radius;
	y = center_y - radius;
	while (y <= center_y + radius)
	{
		while (x <= center_x + radius)
		{
			if ((pow(x - center_x, 2)) + pow(y - center_y, 2) <= radius_squared)
				put_pixel(img, x, y, 0XFF0000);
			x++;
		}
		y++;
		x = center_x - radius;
	}
}