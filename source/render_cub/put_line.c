/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:55:05 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/05 20:59:40 by phemsi-a         ###   ########.fr       */
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
 }
 
 static void	increment(int *x, int *y, int *x_increment, int *y_increment)
 {
 	*x += *x_increment;
 	*y += *y_increment;
 }
 
 void   init(t_bresenham *n)
 {
     *n = (t_bresenham){0};
 }
 
 void		put_line(t_data *img, int *player_pos, int x2, int y2)
 {
 	t_bresenham	n;
 	int			x;
 	int			y;
 
    init(&n);
 	x = player_pos[X];
 	y = player_pos[Y];
 	ft_memset(n.increment, 0, sizeof(n.increment));
 	n.delta[X] = x2 - x;
 	n.delta[Y] = y2 - y;
 	define_increment(&n);
 	define_longest(&n);
 	n.numerator = n.longest / 2;
 	while (n.i <= n.longest)
 	{
 		put_pixel(img, x, y, color_picker(img->c.red, img->c.green, img->c.blue));
 		n.numerator += n.shortest;
 		if (n.numerator > n.longest)
 		{
 			n.numerator -= n.longest;
 			increment(&x, &y, &n.increment[X][0], &n.increment[Y][0]);
 		}
 		else
 			increment(&x, &y, &n.increment[X][1], &n.increment[Y][1]);
 		n.i++;
 	}
 }
