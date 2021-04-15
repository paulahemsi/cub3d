/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/15 01:40:02 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	update_player(t_player *player, t_settings *cub)
{
	float step;
	float new_position[2];
	float angle;

	player->angle += player->direction[TURN] * player->rotate_speed;
	player->angle = normalize_angle(player->angle);
	step = player->direction[MOVE] * player->speed;
	if (player->direction[SIDE])
		angle = PI / 2;
	else
		angle = 0;
	new_position[X] = player->pos[X] + (cos(player->angle + angle) * step);
	new_position[Y] = player->pos[Y] + (sin(player->angle + angle) * step);
	if (is_tile_free(new_position, cub, TRUE))
	{
		player->pos[X] = new_position[X];
		player->pos[Y] = new_position[Y];
	}
}

static int	update(t_data *img)
{
	t_ray	rays[img->cub->screen[WIDTH]];

	if (img->ptr)
		mlx_destroy_image(img->mlx_ptr, img->ptr);
	img->ptr = mlx_new_image(img->mlx_ptr, img->cub->screen[WIDTH], img->cub->screen[HEIGHT]);
	img->data = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
								&img->line_length, &img->endian);
	put_background(img, img->cub);
	raycasting(img, img->cub, rays);
	put_walls(img, rays);
	update_player(&img->cub->player, img->cub);
	if (img->cub->map.show_minimap == TRUE)
		render_minimap(img, rays);
	if (!(img->cub->save))
		mlx_put_image_to_window(img->mlx_ptr, img->window_ptr, img->ptr, 0, 0);
	return (0);
}

static void	check_resolution_limits(t_data *img, t_settings *cub)
{
	int		max[2];

	mlx_get_screen_size(img->mlx_ptr, &max[X], &max[Y]);
	if (cub->screen[WIDTH] > max[X])
		cub->screen[WIDTH] = max[X];
	if (cub->screen[HEIGHT] > max[Y])
		cub->screen[HEIGHT] = max[Y];
	cub->center[X] = floor(cub->screen[WIDTH] / 2);
	cub->center[Y] = floor(cub->screen[HEIGHT] / 2);
	cub->player.plane_dist = floor((cub->screen[WIDTH] / 2) / tan(HALF_FOV));
	cub->ray.step= FOV / cub->screen[WIDTH];
	cub->ray.total = cub->screen[WIDTH];
}

void		render_cub(t_settings *cub, t_data *img)
{
	check_resolution_limits(img, cub);
	if (!(cub->save))
	{
		img->window_ptr = mlx_new_window(img->mlx_ptr, cub->screen[WIDTH], cub->screen[HEIGHT],
									"cub3D");
		if (!(img->window_ptr))
			return_error(-9);
	}
	img->cub = cub;
	img->ptr = NULL;
	update(img);
	if (cub->save)
		save_bmp(img);
	mlx_loop_hook(img->mlx_ptr, update, img);
	//mlx_mouse_hook(img.window_ptr, mouse_clicked, &img);
	//mlx_mouse_hide(img.mlx_ptr, img.window_ptr);
	mlx_hook(img->window_ptr, 2, 1L<<0, key_pressed, img);
	mlx_hook(img->window_ptr, 3, 1L<<1, key_released, img);
	mlx_hook(img->window_ptr, 33, 1L<<17, close_cub, img);
	mlx_loop(img->mlx_ptr);
}
