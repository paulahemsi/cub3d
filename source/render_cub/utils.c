/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:01:20 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/06 00:46:48 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

float	degrees_to_radians(int degree)
{
	return ((float)degree * PI / 180);
}

int		radiands_to_degrees(float radian)
{
	return (floor(radian * 180 / PI));
}

void	define_img_colors(t_data *img, int red, int green, int blue)
{
	img->c.red = red;
	img->c.green = green;
	img->c.blue = blue;
}