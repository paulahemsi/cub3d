/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/26 11:47:17 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void		my_mlx_pixel_put(t_data *img, int pos_x, int pos_y, int color)
{
	char	*dst;
	int		offset;

	offset = (pos_y * img->line_length + pos_x * (img->bits_per_pixel / 8));
	dst = img->data + offset;
	*(unsigned int*)dst = color;
}

static void		render_line(t_configs *configs, t_data *img, int pos_x, int pos_y)
{
	while (pos_x < configs->window_width)
	{
		my_mlx_pixel_put(img, pos_x, pos_y, 0x00FFFFFF);
		pos_x++;
	}
}

int deal_key(int key, void *param)
{
	ft_putchar('x');
	return (0);
}

void			render_cub(t_configs *configs)
{
	void    *mlx_ptr;
	void    *window_ptr;
	t_data	img;

	mlx_ptr = mlx_init();
	window_ptr = mlx_new_window(mlx_ptr, configs->window_width, configs->window_height, "cub3D");
	img.ptr = mlx_new_image(mlx_ptr, configs->window_width, configs->window_height);
	img.data = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	render_line(configs, &img, 50, 50);
	mlx_put_image_to_window(mlx_ptr, window_ptr, img.ptr, 0, 0);
	mlx_key_hook(window_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
}
