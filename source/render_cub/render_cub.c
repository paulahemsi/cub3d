/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/26 13:23:40 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	update_player(t_player *player, t_cub *cub)
{
	float	step;
	float	angle;
	float	new_position[2];

	player->angle += player->direction[TURN] * player->rotate_speed;
	player->angle = normalize_angle(player->angle);
	step = player->direction[MOVE] * player->speed;
	if (player->direction[SIDE])
		angle = PI / 2;
	else
		angle = 0;
	new_position[X] = player->pos[X] + (cos(player->angle + angle) * step);
	new_position[Y] = player->pos[Y] + (sin(player->angle + angle) * step);
	if (is_tile_free(new_position, &cub->settings, &cub->game.map, TRUE))
	{
		player->pos[X] = new_position[X];
		player->pos[Y] = new_position[Y];
	}
}

static int	update(t_cub *cub)
{
	t_ray	*rays;

	rays = (t_ray *)malloc(cub->settings.screen[WIDTH] * sizeof(t_ray));
	if (cub->img.ptr)
		mlx_destroy_image(cub->mlx_ptr, cub->img.ptr);
	cub->img.ptr = mlx_new_image(cub->mlx_ptr,
			cub->settings.screen[WIDTH],
			cub->settings.screen[HEIGHT]);
	cub->img.data = mlx_get_data_addr(cub->img.ptr, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	put_background(cub, &cub->settings.ceiling, &cub->settings.floor,
		&cub->game.color);
	raycasting(cub, rays);
	put_walls(cub, rays);
	put_sprite(cub->game.sprites, &cub->game.player,&cub->settings, cub);
	update_player(&cub->game.player, cub);
	if (cub->toggle.show_minimap == TRUE)
		render_minimap(cub, &cub->game.map, rays);
	if (!(cub->toggle.save))
		mlx_put_image_to_window(cub->mlx_ptr, cub->window_ptr,
			cub->img.ptr, 0, 0);
	free(rays);
	return (0);
}

void	render_cub(t_cub *cub)
{
	if (!(cub->toggle.save))
	{
		cub->window_ptr = mlx_new_window(cub->mlx_ptr,
				cub->settings.screen[WIDTH],
				cub->settings.screen[HEIGHT],
				"cub3D");
		if (!(cub->window_ptr))
			return_error(-9);
	}
	cub->img.ptr = NULL;
	update(cub);
	if (cub->toggle.save)
		save_bmp(cub);
	mlx_loop_hook(cub->mlx_ptr, update, cub);
	mlx_hook(cub->window_ptr, 2, 1L << 0, key_pressed, cub);
	mlx_hook(cub->window_ptr, 3, 1L << 1, key_released, cub);
	mlx_hook(cub->window_ptr, 33, 1L << 17, close_cub, cub);
	mlx_loop(cub->mlx_ptr);
}
/*
** mlx_mouse_hook(img.window_ptr, mouse_clicked, &img);
** mlx_mouse_hide(img.mlx_ptr, img.window_ptr);
*/