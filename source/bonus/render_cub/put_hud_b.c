/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hud_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 03:17:40 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/02 19:38:19 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static int	get_hud_color(t_texture *texture, int x, int y)
{
	return (*(unsigned int *)(texture->img.data
		+ (y * texture->img.line_length + x
			* (texture->img.bits_per_pixel / 8))));
}

void	put_hud(t_texture *textures, t_cub *cub)
{
	int	x;
	int	y;
	int y_hud;
	int	color;
	t_texture texture;

	x = 0;
	//****proteção para testes********
	if (cub->game.hud_id > 5)
		cub->game.hud_id = 5;
	//********************************
	texture = textures[cub->game.hud_id];
	while (x < cub->settings.screen[WIDTH])
	{
		y = 0;
		y_hud = 0;
		while (y < cub->settings.screen[HEIGHT])
		{
			if ((y > 486))
			{
				color = get_hud_color(&texture, x, y_hud);
				if (color != 0x000000)
					put_pixel(&cub->img, x, y, color);
				y_hud++;
			}
			y++;
		}
		x++;
	}
}
