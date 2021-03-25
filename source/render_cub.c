/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/25 20:45:07 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void		my_mlx_pixel_put(t_data *data, int pos_x, int pos_y, int color)
{
	char	*dst;
	int		offset;

	offset = (pos_y * data->line_length + pos_x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
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

void			render_cub(t_configs *configs)
{
	void    *mlx;
	void    *mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, configs->window_width, configs->window_height, "cub3D");
	img.img = mlx_new_image(mlx, configs->window_width, configs->window_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	render_line(configs, &img, 50, 50);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
