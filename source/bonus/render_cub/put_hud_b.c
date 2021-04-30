/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hud_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 03:17:40 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 21:11:58 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static int	get_hud_color(t_texture *texture, int x, int y)
{
	return (*(unsigned int *)(texture->img.data
		+ (y * texture->img.line_length + x
			* (texture->img.bits_per_pixel / 8))));
}

void	put_hud(t_texture *texture, t_cub *cub)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < cub->settings.screen[WIDTH])
	{
		y = 0;
		while (y < cub->settings.screen[HEIGHT])
		{
			if ((x > 865 && y < 223) || (y > 486))
			{
				color = get_hud_color(texture, x, y);
				if (color < 1000 || color > 70000)
					put_pixel(&cub->img, x, y, color);
			}
			y++;
		}
		x++;
	}
}
