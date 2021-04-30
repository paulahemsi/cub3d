/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:56:02 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 21:14:40 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

int	color_picker(unsigned char red, unsigned char green,
							unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}

void	define_img_colors(t_rgb *color, int red, int green, int blue)
{
	color->red = red;
	color->green = green;
	color->blue = blue;
}

void	put_pixel(t_data *img, int pos_x, int pos_y, int color)
{
	char	*dst;
	int		offset;

	offset = (pos_y * img->line_length + pos_x * (img->bits_per_pixel / 8));
	dst = img->data + offset;
	*(unsigned int *)dst = color;
}
