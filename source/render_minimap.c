/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:23:03 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/02 11:26:29 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	render_rays(t_data *img)
{
	float	atan;
	int		r;
	int		dof;

	img->cub->ray.angle = img->cub->player.angle;
	r = 0;
	while (r < 1)
	{
		dof = 0;
		atan = -1 / tan(img->cub->ray.angle);
		if (img->cub->ray.angle > PI) //*ray olhando pra baixo
		{
			
		}
		r++;
	}
}

static void	render_player(t_data *img, t_player *player)
{
	put_circle(img, player->pos[X], player->pos[Y], player->radius);
	printf("angle: %lf\n", img->cub->player.angle);
	put_line(img, img->cub->player.pos, img->cub->player.pos[X] + cos(img->cub->player.angle) * 50, img->cub->player.pos[Y] + sin(img->cub->player.angle) * 50);
}

void	render_minimap(t_data *img)
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
	render_rays(img);
	
	render_player(img, &img->cub->player);
}
