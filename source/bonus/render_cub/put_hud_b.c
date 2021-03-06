/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hud_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 03:17:40 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/06 23:08:12 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static void	put_skull(t_texture skull, t_cub *cub)
{
	int	pos[2];
	int	pos_skull[2];
	int	color;

	pos[X] = 541;
	pos_skull[X] = 0;
	while (pos[X] < (541 + 160))
	{
		pos[Y] = 490;
		pos_skull[Y] = 0;
		while (pos[Y] < 692)
		{
			color = get_hud_color(&skull, pos_skull[X], pos_skull[Y]);
			if (color != 0x000000)
				put_pixel(&cub->img, pos[X], pos[Y], color);
			pos_skull[Y]++;
			pos[Y]++;
		}
		pos_skull[X]++;
		pos[X]++;
	}
}

static void	put_glasses(t_texture glasses, t_cub *cub)
{
	int	pos[2];
	int	pos_glasses[2];
	int	color;

	pos[X] = 556;
	pos_glasses[X] = 0;
	while (pos[X] < (556 + 142))
	{
		pos[Y] = 587;
		pos_glasses[Y] = 0;
		while (pos[Y] < (587 + 81))
		{
			color = get_hud_color(&glasses, pos_glasses[X], pos_glasses[Y]);
			if (color != 0x000000)
				put_pixel(&cub->img, pos[X], pos[Y], color);
			pos_glasses[Y]++;
			pos[Y]++;
		}
		pos_glasses[X]++;
		pos[X]++;
	}
}

static void	draw_hud(t_texture texture, t_cub *cub, int x, int x_end)
{
	int	y;
	int	hud[2];
	int	color;

	hud[X] = 0;
	while (x < x_end)
	{
		y = 0;
		hud[Y] = 0;
		while (y < cub->settings.screen[HEIGHT])
		{
			if ((y > 486))
			{
				color = get_hud_color(&texture, hud[X], hud[Y]);
				if (color > 0x111111)
					put_pixel(&cub->img, x, y, color);
				hud[Y]++;
			}
			y++;
		}
		hud[X]++;
		x++;
	}
}

static void	draw_lifebar(t_texture hearts, t_cub *cub)
{
	int	pos[2];
	int	pos_hearts[2];
	int	color;

	pos[X] = 896;
	pos_hearts[X] = 6;
	while (pos[X] < cub->settings.screen[WIDTH])
	{
		pos[Y] = 0;
		pos_hearts[Y] = 0;
		while (pos[Y] < 201)
		{
			color = get_hud_color(&hearts, pos_hearts[X], pos_hearts[Y]);
			if (color != 0x000000)
				put_pixel(&cub->img, pos[X], pos[Y], color);
			pos_hearts[Y]++;
			pos[Y]++;
		}
		pos_hearts[X]++;
		pos[X]++;
	}
}

void	put_hud(t_texture *textures, t_cub *cub)
{
	draw_hud(textures[0], cub, 0, cub->settings.screen[WIDTH]);
	if (cub->game.item.red_k)
		draw_hud(textures[1], cub, 0, 162);
	if (cub->game.item.green_k)
		draw_hud(textures[2], cub, 162, 320);
	if (cub->game.item.blue_k)
		draw_hud(textures[3], cub, 320, 494);
	if (cub->game.item.glasses)
		draw_hud(textures[4], cub, 791, 965);
	if (cub->game.item.map)
		draw_hud(textures[5], cub, 1006, 1203);
	if (cub->game.life == 0)
		put_skull(textures[7], cub);
	if (cub->toggle.night_mode == TRUE)
		put_glasses(textures[6], cub);
	draw_lifebar(cub->game.hearts[cub->game.life], cub);
}
