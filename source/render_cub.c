/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/27 01:09:19 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		color_picker(unsigned char red, unsigned char green, unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}


static void		my_mlx_pixel_put(t_data *img, int pos_x, int pos_y, int color)
{
	char	*dst;
	int		offset;

	offset = (pos_y * img->line_length + pos_x * (img->bits_per_pixel / 8));
	dst = img->data + offset;
	*(unsigned int*)dst = color;
}

void	fill_image(t_data *img, int color)
{
	int	pos_x;
	int	pos_y;
	int color_init;
	int factor;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	
	r = 0;
	g = 50;
	b = 120;
	pos_x = 0;
	pos_y = 0;
	
	while (pos_y <= img->height)
	{
		color = color_picker(r, g, b);
		while (pos_x <= img->width)
		{
			my_mlx_pixel_put(img, pos_x, pos_y, color);
			pos_x++;
		}
		pos_y++;
		if (r < 254)
			r++;
		else if (g < 255)
			g++;
		pos_x = 0;
	}
}

void	draw_square(t_data *img, int pos_x, int pos_y, int color, t_configs *configs)
{
	int x_init;

	x_init = pos_x;
	while (pos_y < img->height)
	{
		while (pos_x < img->width)
		{
			my_mlx_pixel_put(img, pos_x, pos_y, color);
			pos_x++;
		}
		pos_y++;
		pos_x = x_init;
	}
}

void draw_minimap(t_configs *config, t_data *img)
{
	unsigned int	i;
	unsigned int	j;
	int				pos_x;
	int				pos_y;
	int				color;

	i = 0;
	while (i < config->map.total_row)
	{
		j = 0;
		while (j < config->map.total_column)
		{
			pos_x = j * (config->tile_size[x]);
			pos_y = i * (config->tile_size[y]);
			if (config->map.row[i][j] == '0')
				color = 0xFFFFFFFF;
			else if (ft_strchr("NSWE", config->map.row[i][j]))
				color = 0x00FF0000;
			else
				color = 0x00000000;
			draw_square(img, pos_x, pos_y, color, config);
			j++;
		}
		i++;
	}
}

static void		render_line(t_configs *configs, t_data *img, int pos_x, int pos_y)
{
	while (pos_x < configs->window_width)
	{
		my_mlx_pixel_put(img, pos_x, pos_y, 0x00FF00FF);
		pos_x++;
	}
}

void			render_cub(t_configs *configs)
{
	t_data	img;

	if (!(img.mlx_ptr = mlx_init()))
		return_error(-8);
	img.window_ptr = mlx_new_window(img.mlx_ptr, configs->window_width, configs->window_height, "cub3D");
	if (!(img.window_ptr))
		return_error(-9);
	img.width = configs->window_width;
	img.height = configs->window_height;
	img.ptr = mlx_new_image(img.mlx_ptr, img.width, img.height);
	img.data = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	fill_image(&img, color_picker(0, 30, 50));
	draw_minimap(configs, &img);
	//render_line(configs, &img, 50, 50);
	mlx_put_image_to_window(img.mlx_ptr, img.window_ptr, img.ptr, 0, 0);
	mlx_mouse_hook(img.window_ptr, mouse_clicked, &img);
	mlx_key_hook(img.window_ptr, key_is_pressed, &img);
	if (img.mlx_ptr)
	{
		mlx_destroy_image(img.mlx_ptr, img.ptr);
		
		mlx_loop(img.mlx_ptr);
	}
}
