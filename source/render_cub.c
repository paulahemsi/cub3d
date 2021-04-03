/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/02 22:18:50 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	update(t_data *img)
{
	if (img->ptr)
		mlx_destroy_image(img->mlx_ptr, img->ptr);
	img->ptr = mlx_new_image(img->mlx_ptr, img->cub->width, img->cub->height);
	img->data = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
								&img->line_length, &img->endian);
	//render_minimap(img);
	put_walls(img);
	mlx_put_image_to_window(img->mlx_ptr, img->window_ptr, img->ptr, 0, 0);
	return (0);
}

void		render_cub(t_configs *cub)
{
	t_data	img;

	if (!(img.mlx_ptr = mlx_init()))
		return_error(-8);
	img.window_ptr = mlx_new_window(img.mlx_ptr, cub->width, cub->height,
									"cub3D");
	if (!(img.window_ptr))
		return_error(-9);
	img.cub = cub;
	img.ptr = NULL;
	printf("angle: %lf\n", cub->player.angle);
	mlx_loop_hook(img.mlx_ptr, update, &img);
	mlx_mouse_hook(img.window_ptr, mouse_clicked, &img);
	mlx_hook(img.window_ptr, 2, 1L<<0, key_pressed, &img);
	mlx_hook(img.window_ptr, 3, 1L<<1, key_released, &img);
	mlx_hook(img.window_ptr, 33, 1L<<17, close_cub, &img);
	mlx_loop(img.mlx_ptr);
}
