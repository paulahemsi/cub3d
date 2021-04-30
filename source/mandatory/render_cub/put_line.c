/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:55:05 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/30 21:14:18 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/cub.h"

static void	define_increment(t_bresenham *n)
{
	if (n->delta[X] < 0)
	{
		n->inc[X][0] = -1;
		n->inc[X][1] = -1;
	}
	else if (n->delta[X] > 0)
	{
		n->inc[X][0] = 1;
		n->inc[X][1] = 1;
	}
	if (n->delta[Y] < 0)
		n->inc[Y][0] = -1;
	else if (n->delta[Y] > 0)
		n->inc[Y][0] = 1;
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
			n->inc[Y][1] = -1;
		else if (n->delta[Y] > 0)
			n->inc[Y][1] = 1;
		n->inc[X][1] = 0;
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
	ft_memset(n->inc, 0, sizeof(n->inc));
	n->i = -1;
}

void	put_line(t_cub *cub, int *pos, int x2, int y2)
{
	t_bresenham	n;
	int			init[2];
	int			color;

	init_values(&n, init, pos);
	n.delta[X] = x2 - init[X];
	n.delta[Y] = y2 - init[Y];
	define_increment(&n);
	define_longest(&n);
	while (n.i++ <= n.longest)
	{
		color = color_picker(cub->game.color.red, cub->game.color.green,
				cub->game.color.blue);
		if (is_inside_screen(cub->settings.screen, init[X], init[Y]))
			put_pixel(&cub->img, init[X], init[Y], color);
		n.numerator += n.shortest;
		if (n.numerator > n.longest)
		{
			n.numerator -= n.longest;
			increment(&init[X], &init[Y], &n.inc[X][0], &n.inc[Y][0]);
		}
		else
			increment(&init[X], &init[Y], &n.inc[X][1], &n.inc[Y][1]);
	}
}
