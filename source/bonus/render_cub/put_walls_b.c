/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_walls_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 03:23:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/10 23:29:26 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static int	define_direction(t_game *game, t_ray *rays, int ray, t_texture t)
{
	if (rays[ray].vertical_hit)
	{
		if (rays[ray].left)
			game->wall_direction = EAST;
		else
			game->wall_direction = WEST;
	}
	else
	{
		if (rays[ray].up)
			game->wall_direction = SOUTH;
		else
			game->wall_direction = NORTH;
	}
	if (rays[ray].vertical_hit)
		return ((int)rays[ray].hit[Y] % t.width);
	else
		return ((int)rays[ray].hit[X] % t.width);
}

static int	get_texture_color(t_cub *cub, int y, int offset_x)
{
	t_texture	texture;
	int			screen_height;
	int			offset[2];
	int			dist_to_top;
	int			glitch;

	texture = cub->game.texture[cub->game.wall_direction];
	screen_height = cub->settings.screen[HEIGHT];
	if (cub->settings.level == 2)
		glitch = y;
	else
		glitch = 0;
	offset[X] = offset_x + glitch;
	dist_to_top = y + (cub->game.wall_height / 2) - (screen_height / 2);
	offset[Y] = dist_to_top * ((float)texture.height / cub->game.wall_height);
	return (*(unsigned int *)(texture.img.data
		+ (offset[Y] * texture.img.line_length + offset[X]
			* (texture.img.bits_per_pixel / 8))));
}

static void	draw_wall(t_cub *cub, int *init, int y_end, int offset_x)
{
	int	color;
	int	y;

	y = init[Y];
	while (y <= y_end)
	{
		if ((y >= 0) && (y <= cub->settings.screen[HEIGHT]))
		{
			color = get_texture_color(cub, y, offset_x);
			if (color != 0x000000)
				put_pixel(&cub->img, init[X], y, color);
		}
		y++;
	}
}

static void	define_limits(t_cub *cub, int *init, int *end_y, int ray)
{
	init[X] = ray;
	init[Y] = cub->settings.center[Y] - (cub->game.wall_height / 2);
	if (init[Y] < 0)
		init[Y] = 0;
	*end_y = cub->settings.center[Y] + (cub->game.wall_height / 2);
	if (*end_y > cub->settings.screen[HEIGHT])
		*end_y = cub->settings.screen[HEIGHT];
}

void	put_walls(t_cub *cub, t_ray *rays, t_toggle *t)
{
	int		ray;
	int		init[2];
	int		end_y;
	int		offset_x;

	ray = -1;
	while (++ray < cub->game.ray.total)
	{
		cub->game.is_texture = FALSE;
		if (cub->game.win || cub->settings.level == 2)
			cub->game.is_texture = TRUE;
		if (ft_isalpha(rays[ray].wall_content))
			cub->game.is_texture = FALSE;
		cub->game.wall_height = ((TILE_SIZE / rays[ray].dist)
				* cub->game.player.plane_dist);
		define_limits(cub, init, &end_y, ray);
		offset_x = define_direction(&cub->game, rays, ray,
				cub->game.texture[cub->game.wall_direction]);
		define_wall_colors(cub, rays, ray);
		if (cub->game.is_texture
			&& (t->night_mode != TRUE) && (t->debug != TRUE))
			draw_wall(cub, init, end_y, offset_x);
		else
			put_line(cub, init, init[X], end_y);
	}
}
