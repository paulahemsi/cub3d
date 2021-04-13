/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/13 04:05:12 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"


static int	update(t_data *img)
{
	t_ray	rays[img->cub->screen_width];

	if (img->ptr)
		mlx_destroy_image(img->mlx_ptr, img->ptr);
	img->ptr = mlx_new_image(img->mlx_ptr, img->cub->screen_width, img->cub->screen_height);
	img->data = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
								&img->line_length, &img->endian);
	put_background(img, img->cub);
	raycasting(img, img->cub, rays);
	put_walls(img, rays);
	if (img->cub->map.show_minimap == TRUE)
		render_minimap(img, rays);
	if (!(img->cub->save))
		mlx_put_image_to_window(img->mlx_ptr, img->window_ptr, img->ptr, 0, 0);
	return (0);
}

static void	check_resolution_limits(t_data *img, t_configs *cub)
{
	int		max[2];
	
	mlx_get_screen_size(img->mlx_ptr, &max[X], &max[Y]);
	if (cub->screen_width > max[X])
		cub->screen_width = max[X];
	if (cub->screen_height > max[Y])
		cub->screen_height = max[Y];
	cub->center[X] = floor(cub->screen_width / 2);
	cub->center[Y] = floor(cub->screen_height / 2);
	cub->player.plane_dist = floor((cub->screen_width / 2) / tan(HALF_FOV));
	cub->ray.step= FOV / cub->screen_width;
	cub->ray.total = cub->screen_width;
}

void		render_cub(t_configs *cub)
{
	t_data	img;

	if (!(img.mlx_ptr = mlx_init()))
		return_error(-8);
	check_resolution_limits(&img, cub);
	if (!(cub->save))
	{
		img.window_ptr = mlx_new_window(img.mlx_ptr, cub->screen_width, cub->screen_height,
									"cub3D");
		if (!(img.window_ptr))
			return_error(-9);
	}
	img.cub = cub;
	img.ptr = NULL;
	update(&img);
	if (cub->save)
		save_bmp(&img);
	mlx_loop_hook(img.mlx_ptr, update, &img);
	mlx_mouse_hook(img.window_ptr, mouse_clicked, &img);
	mlx_mouse_hide(img.mlx_ptr, img.window_ptr);
	mlx_hook(img.window_ptr, 2, 1L<<0, key_pressed, &img);
	mlx_hook(img.window_ptr, 3, 1L<<1, key_released, &img);
	mlx_hook(img.window_ptr, 33, 1L<<17, close_cub, &img);
	mlx_loop(img.mlx_ptr);
}
