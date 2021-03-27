/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:56:02 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/27 17:30:56 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	color_picker(unsigned char red, unsigned char green,
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

void		put_square(t_data *img, int pos_x, int pos_y, int color)
{
	int x_init;

	x_init = pos_x;
	while (pos_y < img->cub->height)
	{
		while (pos_x < img->cub->width)
		{
			put_pixel(img, pos_x, pos_y, color);
			pos_x++;
		}
		pos_y++;
		pos_x = x_init;
	}
}

void		line(t_configs *cub, t_data *img, int pos_x, int pos_y)
{
	while (pos_x < cub->width)
	{
		put_pixel(img, pos_x, pos_y, 0x00FF00FF);
		pos_x++;
	}
}
