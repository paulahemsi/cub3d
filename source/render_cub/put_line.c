/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:55:05 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/17 23:22:47 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	define_increment(t_bresenham *n)
{
	if (n->delta[X] < 0)
	{
		n->increment[X][0] = -1;
		n->increment[X][1] = -1;
	}
	else if (n->delta[X] > 0)
	{
		n->increment[X][0] = 1;
		n->increment[X][1] = 1;
	}
	if (n->delta[Y] < 0)
		n->increment[Y][0] = -1;
	else if (n->delta[Y] > 0)
		n->increment[Y][0] = 1;
}

static void	define_longest(t_bresenham *n)
{
	n->longest = abs(n->delta[X]);
	n->shortest = abs(n->delta[Y]);
	if ((n->shortest > n->longest))
	{
		n->longest = abs(n->delta[Y]);
		n->shortest = abs(n->delta[X]);
		if (n->delta[Y] < 0)
			n->increment[Y][1] = -1;
		else if (n->delta[Y] > 0)
			n->increment[Y][1] = 1;
		n->increment[X][1] = 0;
	}
	n->numerator = n->longest / 2;
}

static void	increment(int *x, int *y, int *x_increment, int *y_increment)
{
	*x += *x_increment;
	*y += *y_increment;
}

static void	init_values(t_bresenham *n, int *init, int *pos)
{
	*n = (t_bresenham){0};
	init[X] = pos[X];
	init[Y] = pos[Y];
	ft_memset(n->increment, 0, sizeof(n->increment));
}

static int	get_texture_color(int *init, int *offset, t_cub *cub, t_bresenham *n)
{
	int		main_offset;
	t_data texture;
	
	texture = cub->game.texture[SOUTH].img;
	offset[Y] = 1;//(init[Y] - n->i) * ((float)cub->game.texture[SOUTH].height / cub->game.wall_height);
	//ft_printf("offset[y], o polêmico: %i\nn->i em que estamos: %i\ninit[Y]: %i\nheight da text: %i\nWall_height: %i\n", offset[Y], n->i, init[Y], cub->game.texture[SOUTH].height, cub->game.wall_height);
	main_offset = (offset[Y] * texture.line_length + offset[X] * (texture.bits_per_pixel / 8));
	return (*(unsigned int *)(texture.data + main_offset + 2) << 16 |
			*(unsigned int *)(texture.data + main_offset + 1) << 8 |
			*(unsigned int *)(texture.data + main_offset + 0) << 0);
	
	// int			color;
	
	// // color = (cub->game.texture[NORTH].img) + (cub->game.texture[NORTH].height * offset[Y] *
	// // 	(cub->game.texture[NORTH].img->bits_per_pixel / 8)) + (offset[X] * (cub->game.texture[NORTH].img->bits_per_pixel / 8));
	// color = cub->game.texture[NORTH].img.data[(cub->game.texture[NORTH].width * cub->offset[Y]) + cub->offset[X]];
	// return (color);
	// //cub->img.data[(cub->settings.screen[WIDTH] * y)] = color;
}

void		put_line(t_cub *cub, int *pos, int x2, int y2)
{
	t_bresenham	n;
	int			init[2];
	int			color;

	init_values(&n, init, pos);
	n.delta[X] = x2 - init[X];
	n.delta[Y] = y2 - init[Y];
	define_increment(&n);
	define_longest(&n);
	while (n.i <= n.longest)
	{
		if (cub->game.is_texture)
			color = get_texture_color(pos, cub->offset, cub, &n);
		else
			color = color_picker(cub->game.color.red, cub->game.color.green, cub->game.color.blue);
		put_pixel(&cub->img, init[X], init[Y], color);
		n.numerator += n.shortest;
		if (n.numerator > n.longest)
		{
			n.numerator -= n.longest;
			increment(&init[X], &init[Y], &n.increment[X][0], &n.increment[Y][0]);
		}
		else
			increment(&init[X], &init[Y], &n.increment[X][1], &n.increment[Y][1]);
		n.i++;
	}
}
