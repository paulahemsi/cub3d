/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:00:41 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 21:14:22 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

static void	set_sprite_values(t_cub *cub, t_sprite *s, t_player *player)
{
	float	screen_x;

	s->distance = define_distance(player->pos, s->pos);
	s->height = (s->texture.height / s->distance) * player->plane_dist;
	s->width = (s->texture.width / s->distance) * player->plane_dist;
	s->init[Y] = cub->settings.center[Y] - (s->height / 2);
	if (s->init[Y] < 0)
		s->init[Y] = 0;
	s->end[Y] = cub->settings.center[Y] + (s->height / 2);
	if (s->end[Y] > cub->settings.screen[HEIGHT])
		s->end[Y] = cub->settings.screen[HEIGHT];
	s->angle = atan2(s->pos[Y] - player->pos[Y],
			s->pos[X] - player->pos[X]) - player->angle;
	screen_x = tan(s->angle) * player->plane_dist;
	s->init[X] = cub->settings.center[WIDTH] + screen_x;
	s->end[X] = s->init[X] + s->width;
}

static int	get_sprite_color(t_sprite *sprite, t_texture *texture,
		int *pos, t_settings *set)
{
	int	offset[2];
	int	dist_to_top;
	int	diff_x;

	diff_x = (pos[X] - sprite->init[X]);
	offset[X] = diff_x * sprite->texture.width / sprite->width;
	if (offset[X] < 0)
		offset[X] *= -1;
	dist_to_top = pos[Y] + (sprite->height / 2) - (set->screen[HEIGHT] / 2);
	offset[Y] = dist_to_top * ((float)texture->height / (float)sprite->height);
	return (*(unsigned int *)(texture->img.data
		+ (offset[Y] * texture->img.line_length
			+ offset[X] * (texture->img.bits_per_pixel / 8))));
}

static void	draw_sprite(t_cub *cub, t_sprite *sprite, t_ray *ray)
{
	int	pos[2];
	int	color;

	pos[X] = (int)sprite->init[X];
	while (pos[X] < sprite->end[X])
	{
		pos[Y] = (int)sprite->init[Y];
		while (pos[Y] < sprite->end[Y])
		{
			if (is_inside_screen(cub->settings.screen, pos[X], pos[Y]))
			{
				if (sprite->distance < ray[pos[X]].dist)
				{
					color = get_sprite_color(sprite, &sprite->texture, pos,
							&cub->settings);
					if (color != 0x000000)
						put_pixel(&cub->img, pos[X], pos[Y], color);
				}
			}
			pos[Y]++;
		}
		pos[X]++;
	}
}

static void	sort_sprites(t_sprite *sprites, t_cub *cub)
{
	t_sprite	temp;
	int			i;

	i = 0;
	while (i < cub->game.num_sprites - 1)
	{
		if (sprites[i].distance < sprites[i + 1].distance)
		{
			temp = sprites[i];
			sprites[i] = sprites[i + 1];
			sprites[i + 1] = temp;
		}
		i++;
	}
}

void	put_sprite(t_sprite *sprites, t_player *player, t_cub *cub, t_ray *ray)
{
	int	i;

	i = 0;
	while (i < cub->game.num_sprites)
	{
		set_sprite_values(cub, &sprites[i], player);
		if (sprites[i].angle > PI)
			sprites[i].angle -= TWO_PI;
		if (sprites[i].angle < -PI)
			sprites[i].angle += TWO_PI;
		sprites[i].angle = fabs(sprites[i].angle);
		if (sprites[i].angle < (HALF_FOV + 0.2))
			sprites[i].visible = TRUE;
		else
			sprites[i].visible = FALSE;
		i++;
	}
	sort_sprites(sprites, cub);
	i = 0;
	while (i < cub->game.num_sprites)
	{
		if (sprites[i].visible)
			draw_sprite(cub, &sprites[i], ray);
		i++;
	}
}
