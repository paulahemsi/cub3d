/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:00:41 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/22 16:33:00 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	calculate_sprite_values(t_sprite *sprite, t_player *player, t_settings *set, t_cub *cub)
{
	float	distance;
	int	init[2];
	int end[2];
	float	dist_to_center;

	distance = sqrt(((sprite->pos[X] - player->pos[X]) * (sprite->pos[X] - player->pos[X])) + ((sprite->pos[Y] - player->pos[Y]) * (sprite->pos[Y] - player->pos[Y])));
	sprite->height = sprite->texture.height / distance * player->plane_dist;
	sprite->width = sprite->height;
	init[Y] = set->center[Y] - (sprite->height / 2);
	if (init[Y] < 0)
		init[Y] = 0;
	end[Y] = set->center[Y] + (sprite->height / 2);
	if (end[Y] > set->screen[HEIGHT])
		end[Y] = set->screen[HEIGHT];
	dist_to_center = tan(sprite->angle * player->plane_dist);
	init[X] = set->center[X] + sprite->pos[X] - (sprite->width / 2);
	int i = init[Y];
	while (i < end[Y])
	{
		define_img_colors(&cub->game.color, 255, 0, 0);
		put_line(cub, init, init[X] + sprite->width, init[Y]);
		i++;
		init[Y] = i;
	}
}

static void	clamp_angle(float *angle)
{
	if (*angle < -1 * PI)
		*angle += 2 * PI;
	if (*angle > PI)
		*angle -= 2 * PI;
	*angle = fabs(*angle);
}

void	put_sprites(t_cub *cub, t_sprite *sprite, t_player *player)
{
	int 	i;

	i = 0;
	while (i < cub->game.num_sprites)
	{
		sprite[i].angle = player->angle - atan2(sprite[i].pos[Y] - player->pos[Y], sprite[i].pos[X] - player->pos[X]);
		clamp_angle(&sprite[i].angle);
		if (sprite[i].angle < HALF_FOV)
			calculate_sprite_values(&sprite[i], player, &cub->settings, cub);
		i++;
	}
}
