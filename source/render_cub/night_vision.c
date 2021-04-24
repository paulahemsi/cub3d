/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   night_vision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:20:01 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/24 15:54:57 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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
	define_gradient(&night_vision[CEILING], &night_vision[FLOOR], grad);
}

void	night_vision_floor(t_cub *cub, t_rgb *night_vision)
{
	define_img_colors(&cub->game.color,
		night_vision[FLOOR].red,
		night_vision[FLOOR].green,
		night_vision[FLOOR].blue);
}
