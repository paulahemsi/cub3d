/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:00:41 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/26 14:44:47 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"


static void	set_sprite_values(t_cub *cub, t_sprite *sprite, t_player *player)
{
	float screen_x;
	
	sprite->distance = sqrt(((sprite->pos[X] - player->pos[X]) * (sprite->pos[X] - player->pos[X])) + ((sprite->pos[Y] - player->pos[Y]) * (sprite->pos[Y] - player->pos[Y])));
	sprite->height = (sprite->texture.height / sprite->distance) * player->plane_dist;
	sprite->width = (sprite->texture.width / sprite->distance) * player->plane_dist;
	sprite->init[Y] = cub->settings.center[Y] - (sprite->height / 2);
	if (sprite->init[Y] < 0)
		sprite->init[Y] = 0;
	sprite->end[Y] = cub->settings.center[Y] + (sprite->height / 2);
	if (sprite->end[Y] > cub->settings.screen[HEIGHT])
		sprite->end[Y] = cub->settings.screen[HEIGHT];
	sprite->angle = atan2(sprite->pos[Y] + (sprite->height / 2) - player->pos[Y], sprite->pos[X] + (sprite->width / 2) - player->pos[X]) - player->angle;
	screen_x = tan(sprite->angle) * player->plane_dist;
	sprite->init[X] = cub->settings.center[WIDTH] + screen_x - (sprite->width / 2);
	sprite->end[X] = sprite->init[X] + sprite->width;
}

static void	draw_sprite(t_cub *cub, t_sprite *sprite, t_player *player)
{
	float	y;
	float	x;
	int		dist_to_top;

	x = sprite->init[X];
	while (x < sprite->end[X])
	{
		y = sprite->init[Y];
		while (y < sprite->end[Y])
		{
			if (is_inside_screen(cub->settings.screen, x, y))
				put_pixel(&cub->img, x, y, 0xFFFF0077);
			y++;
		}
		x++;
	}
}

void	put_sprite(t_sprite *sprites, t_player *player, t_settings *set, t_cub *cub)
{

	if (cub->game.sprite)
	{
		int i = 0;
		while (i < cub->game.num_sprites)
		{
			if (sprites[i].visible == TRUE)
			{
				set_sprite_values(cub, &sprites[i], player);
				draw_sprite(cub, &sprites[i], player);
			}
			cub->game.sprites[i].visible = FALSE;
			i++;
		}
	}
	cub->game.sprite = FALSE;

}
