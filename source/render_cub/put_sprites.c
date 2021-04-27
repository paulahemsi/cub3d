/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:00:41 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/27 14:24:41 by phemsi-a         ###   ########.fr       */
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
	sprite->angle = atan2(sprite->pos[Y] - player->pos[Y], sprite->pos[X] - player->pos[X]) - player->angle;
	screen_x = tan(sprite->angle) * player->plane_dist;
	sprite->init[X] = cub->settings.center[WIDTH] + screen_x - (sprite->width / 2);
	sprite->end[X] = sprite->init[X] + sprite->width;
}

static int	get_sprite_color(t_sprite *sprite, t_texture *texture, int x, int y, t_settings *set)
{
	int offset[2];
	int dist_to_top;

	offset[X] = (x - sprite->init[X]) * sprite->texture.width / sprite->width;
	// if (offset[X] < 0)
	// offset[X] *= -1;
	dist_to_top = y + (sprite->height / 2) - (set->screen[HEIGHT] / 2);
	offset[Y] = dist_to_top * ((float)texture->height / (float)sprite->height);
	return (*(unsigned int *)(texture->img.data + (offset[Y] * texture->img.line_length + offset[X] * (texture->img.bits_per_pixel / 8))));
}

static void	draw_sprite(t_cub *cub, t_sprite *sprite, t_player *player, t_ray *ray)
{
	int	y;
	int	x;
	int	color;

	x = (int)sprite->init[X];
	while (x < sprite->end[X])
	{
		y = (int)sprite->init[Y];
		while (y < sprite->end[Y])
		{
			if (is_inside_screen(cub->settings.screen, x, y))
				if (sprite->distance < ray[x].dist)
				{
					color = get_sprite_color(sprite, &sprite->texture, x, y, &cub->settings);
					if (color != 0x000000)
						put_pixel(&cub->img, x, y, color);
				}
			y++;
		}
		x++;
	}
}

void	put_sprite(t_sprite *sprites, t_player *player, t_cub *cub, t_ray *ray)
{

	if (cub->game.sprite)
	{
		int i = 0;
		while (i < cub->game.num_sprites)
		{
			if (sprites[i].visible == TRUE)
			{
				set_sprite_values(cub, &sprites[i], player);
				draw_sprite(cub, &sprites[i], player, ray);
			}
			cub->game.sprites[i].visible = FALSE;
			i++;
		}
	}
	cub->game.sprite = FALSE; //?precisa?

}
