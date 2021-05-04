/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/04 02:08:54 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static void	create_image(t_cub *cub)
{
	int		*win;
	t_data	*img;

	img = &cub->img;
	win = cub->settings.screen;
	if (img->ptr)
		mlx_destroy_image(cub->mlx_ptr, img->ptr);
	img->ptr = mlx_new_image(cub->mlx_ptr, win[WIDTH], win[HEIGHT]);
	img->data = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

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
	if (is_tile_free(new_position, cub, &cub->game.map, TRUE))
	{
		player->pos[X] = new_position[X];
		player->pos[Y] = new_position[Y];
	}
}

static int	update(t_cub *cub)
{
	t_ray		*rays;
	t_settings	*set;

	set = &cub->settings;
	rays = (t_ray *)malloc(cub->settings.screen[WIDTH] * sizeof(t_ray));
	create_image(cub);
	put_background(cub, &set->ceiling, &cub->settings.floor, &cub->game.color);
	raycasting(cub, rays);
	put_walls(cub, rays, &cub->toggle);
	put_sprite(cub->game.sprites, &cub->game.player, cub, rays);
	update_player(&cub->game.player, cub);
	put_hud(cub->game.hud, cub);
	if (cub->toggle.show_minimap == TRUE)
		render_minimap(cub, &cub->game.map, rays);
	if (!(cub->toggle.save))
		mlx_put_image_to_window(cub->mlx_ptr, cub->window_ptr,
			cub->img.ptr, 0, 0);
	free(rays);
	
	//int	i;

	// i = 0;
	// while (i < cub->game.num_sprites)
	// {
	// 	//ft_printf("sprite[%i].active = %i\n", i, cub->game.sprites[i].active);
	// 	if (cub->game.sprites[i].active)
	// 		mlx_put_image_to_window(cub->mlx_ptr, cub->window_ptr,
	// 		cub->game.sprites[i].texture.img.ptr, 0, i * 100);
	// 	i++;
	// }
	return (0);
}

static void	generate_window(t_cub *cub)
{
	cub->window_ptr = mlx_new_window(cub->mlx_ptr,
			cub->settings.screen[WIDTH],
			cub->settings.screen[HEIGHT],
			"cub3D");
	if (!(cub->window_ptr))
		return_error(cub, -120);
}

void	render_cub(t_cub *cub)
{
	if (!(cub->toggle.save))
		generate_window(cub);
	update(cub);
	if (cub->toggle.save)
		save_bmp(cub);
	mlx_loop_hook(cub->mlx_ptr, update, cub);
	mlx_hook(cub->window_ptr, 2, 1L << 0, key_pressed, cub);
	mlx_hook(cub->window_ptr, 3, 1L << 1, key_released, cub);
	mlx_hook(cub->window_ptr, 33, 1L << 17, close_cub, cub);
	mlx_mouse_hook(cub->window_ptr, mouse_clicked, cub);
	mlx_loop(cub->mlx_ptr);
}
/*
** mlx_mouse_hook(cub->window_ptr, mouse_clicked, cub);
** mlx_mouse_hide(img.mlx_ptr, img.window_ptr);
*/