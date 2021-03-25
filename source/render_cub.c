/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/25 13:34:22 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
	*(unsigned int*)dst = color;
}

void			render_cub(t_configs *configs)
{
	void    *mlx;
	void    *mlx_win;
	int		x;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, configs->window_width, configs->window_height, "cub3D");
	img.img = mlx_new_image(mlx, configs->window_width, configs->window_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	x = configs->window_width/2;
	while (x < configs->window_height)
	{
		my_mlx_pixel_put(&img, x, configs->window_height/2, 0x00FFFFFF);
		x++;	
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
