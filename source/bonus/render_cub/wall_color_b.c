/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:09:28 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/04 20:33:01 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub.h"

static void	define_debug_doors_color(t_rgb *color, char door)
{
	if (door == 'r')
		define_img_colors(color, 153, 0, 0);
	else if (door == 'g')
		define_img_colors(color, 76, 153, 0);
	else if (door == 'b')
		define_img_colors(color, 0, 0, 153);
}

static void	define_horizontal_colors(t_rgb *color, t_ray *rays, int ray)
{
	if (rays[ray].up)
	{
		if (rays[ray].wall_content == '9')
			define_img_colors(color, 54, 133, 128);
		else
			define_img_colors(color, 64, 143, 138);
	}
	else
	{
		if (rays[ray].wall_content == '9')
			define_img_colors(color, 227, 101, 39);
		else
			define_img_colors(color, 237, 111, 49);
	}
}

static void	toggle_debug_colors(t_rgb *color, t_ray *rays, int ray)
{
	if (ft_isalpha(rays[ray].wall_content))
			define_debug_doors_color(color, rays[ray].wall_content);
	else if (rays[ray].vertical_hit)
	{
		if (rays[ray].left)
		{
			if (rays[ray].wall_content == '9')
				define_img_colors(color, 216, 56, 89);
			else
				define_img_colors(color, 226, 66, 99);
		}
		else
		{
			if (rays[ray].wall_content == '9')
				define_img_colors(color, 234, 170, 50);
			else
				define_img_colors(color, 244, 180, 60);
		}
	}
	else
		define_horizontal_colors(color, rays, ray);
}

static void define_doors_color(char door, int color, t_cub *cub)
{
	if (door == 'r')
		define_img_colors(&cub->game.color, color, 0, 0);
	else if (door == 'g')
		define_img_colors(&cub->game.color, 0, color, 0);
	else if (door == 'b')
		define_img_colors(&cub->game.color, 0, 0, color);
}

void	define_wall_colors(t_cub *cub, t_ray *rays, int ray)
{
	int	shadow;
	int	color;
	int	longest_side;

	if (cub->settings.world[HEIGHT] > cub->settings.world[WIDTH])
		longest_side = cub->settings.world[HEIGHT];
	else
		longest_side = cub->settings.world[WIDTH];
	color = 255;
	shadow = floor((rays[ray].dist / 500) * 255);
	color -= shadow;
	if (color > 200)
		color = 200;
	else if (color < 0)
		color = 0;
	if (ft_isalpha(rays[ray].wall_content))
		define_doors_color(rays[ray].wall_content, color, cub);
	else
		define_img_colors(&cub->game.color, color, color, color);
	if (cub->toggle.debug == TRUE)
		toggle_debug_colors(&cub->game.color, rays, ray);
	if (cub->toggle.night_mode == TRUE)
		toggle_night_mode(&cub->game.color, rays, ray);
}
