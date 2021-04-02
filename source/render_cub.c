/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:37:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/01 21:02:12 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	render_player(t_data *img, t_player *player)
{
	put_circle(img, player->pos[X], player->pos[Y], player->radius);
	printf("angle: %lf\n", player->angle);
	put_line(img, player->pos, player->pos[X] + cos(player->angle) * 50, player->pos[Y] + sin(player->angle) * 50);
	// put_line(img, pos_x, pos_y, pos_x, pos_y);
}

static void	render_minimap(t_data *img)
{
	unsigned int	i;
	unsigned int	j;
	int				pos_x;
	int				pos_y;
	int				color;

	i = 0;
	while (i < img->cub->map.total_row)
	{
		j = 0;
		while (j < img->cub->map.total_column)
		{
			pos_x = j * (img->cub->map.tile_size[X]);
			pos_y = i * (img->cub->map.tile_size[Y]);
			if (img->cub->map.row[i][j] == '0')
				color = 0xFFFFFFFF;
			else
				color = 0x00000000;
			put_square(img, pos_x, pos_y, color);
			j++;
		}
		i++;
	}
}

static int	update(t_data *img)
{
	if (img->ptr)
		mlx_destroy_image(img->mlx_ptr, img->ptr);
	img->ptr = mlx_new_image(img->mlx_ptr, img->cub->width, img->cub->height);
	img->data = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
								&img->line_length, &img->endian);
	render_minimap(img);
	render_player(img, &img->cub->player);
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
	mlx_loop_hook(img.mlx_ptr, update, &img);
	mlx_mouse_hook(img.window_ptr, mouse_clicked, &img);
	mlx_hook(img.window_ptr, 2, 1L<<0, key_pressed, &img);
	mlx_hook(img.window_ptr, 3, 1L<<1, key_released, &img);
	mlx_loop(img.mlx_ptr);
}
