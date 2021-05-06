/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   night_vision_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:20:01 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/06 00:49:17 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static void	define_night_vision(t_rgb *night_vision)
{
	night_vision[CEILING].red = 0;
	night_vision[CEILING].green = 116;
	night_vision[CEILING].blue = 0;
	night_vision[FLOOR].red = 1;
	night_vision[FLOOR].green = 7;
	night_vision[FLOOR].blue = 1;
}

void	init_night_vision(t_cub *cub, t_rgb *night_vision, t_gradient *grad)
{
	define_night_vision(night_vision);
	define_img_colors(&cub->game.color,
		night_vision[CEILING].red,
		night_vision[CEILING].green,
		night_vision[CEILING].blue);
	grad++;
	grad--;
	define_gradient(&night_vision[CEILING], &night_vision[FLOOR], grad);
}

void	night_vision_floor(t_cub *cub, t_rgb *night_vision)
{
	define_img_colors(&cub->game.color,
		night_vision[FLOOR].red,
		night_vision[FLOOR].green,
		night_vision[FLOOR].blue);
}

static void	define_doors_color(t_rgb *color, char door)
{
	if (door == 'r')
		define_img_colors(color, 100, 0, 0);
	else if (door == 'g')
		define_img_colors(color, 0, 100, 0);
	else if (door == 'b')
		define_img_colors(color, 0, 0, 100);
	else if (door == 's')
		define_img_colors(color, 123, 255, 18);
}

void	toggle_night_mode(t_rgb *color, t_ray *rays, int ray)
{
	if (ft_isalpha(rays[ray].wall_content))
		define_doors_color(color, rays[ray].wall_content);
	else if (rays[ray].vertical_hit)
	{
		if (rays[ray].left)
			define_img_colors(color, 20, 116, 0);
		else
			define_img_colors(color, 27, 123, 0);
	}
	else
	{
		if (rays[ray].up)
			define_img_colors(color, 62, 180, 6);
		else
			define_img_colors(color, 94, 211, 8);
	}
}
