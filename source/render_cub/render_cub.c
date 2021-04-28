/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/28 16:54:00 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int		is_tile_free_p(float *pos, t_settings *set, t_map *map, int secret_door)
{
	int minimap[2];

	if (pos[X] < 0 || pos[X] >= set->world[WIDTH] || pos[Y] < 0 || pos[Y] >= set->world[HEIGHT])
		return (FALSE);
	minimap[ROW] = floor(pos[Y] / TILE_SIZE);
	minimap[COL] = floor(pos[X] / TILE_SIZE);
	if (minimap[X] >= map->total_column || minimap[Y] >= map->total_row)
		return (FALSE);
	if (map->row[minimap[ROW]][minimap[COL]] == '0')
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == '3' && (secret_door))
		return (TRUE);
	if (map->row[minimap[ROW]][minimap[COL]] == '2')
		return (FALSE);
	return (FALSE);
}

static void	update_player(t_player *player, t_cub *cub)
{
	float	step;
	float	angle;
	float	new_position[2];

	if (cub->toggle.always_running == TRUE)
	{
		cub->game.player.speed = 20;
		cub->game.player.rotate_speed = 4 * PI / 180;
	}
	else
	{
		cub->game.player.speed = 10;
		cub->game.player.rotate_speed = 2.5 * PI / 180;
	}
	player->angle += player->direction[TURN] * player->rotate_speed;
	player->angle = normalize_angle(player->angle);
	step = player->direction[MOVE] * player->speed;
	if (player->direction[SIDE])
		angle = PI / 2;
	else
		angle = 0;
	new_position[X] = player->pos[X] + (cos(player->angle + angle) * step);
	new_position[Y] = player->pos[Y] + (sin(player->angle + angle) * step);
	if (is_tile_free_p(new_position, &cub->settings, &cub->game.map, TRUE))
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
	put_sprite(cub->game.sprites, &cub->game.player, cub, rays);
	update_player(&cub->game.player, cub);
	put_hud(&cub->game.hud, cub);
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
** mlx_mouse_hook(cub->window_ptr, mouse_clicked, cub);
** mlx_mouse_hide(img.mlx_ptr, img.window_ptr);
*/