/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:09:28 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/06 00:52:08 by phemsi-a         ###   ########.fr       */
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
	else if (door == 's')
		define_img_colors(color, 216, 56, 89); 
}

static void	toggle_debug_colors(t_rgb *color, t_ray *rays, int ray)
{
	if (ft_isalpha(rays[ray].wall_content))
			define_debug_doors_color(color, rays[ray].wall_content);
	else if (rays[ray].vertical_hit)
	{
		if (rays[ray].left)
			define_img_colors(color, 226, 66, 99);
		else
			define_img_colors(color, 244, 180, 60);
	}
	else
	{
		if (rays[ray].up)
			define_img_colors(color, 64, 143, 138);
		else
			define_img_colors(color, 237, 111, 49);
	}
}

static void define_doors_color(char door, int color, t_cub *cub)
{
	if (door == 'r')
		define_img_colors(&cub->game.color, color, 0, 0);
	else if (door == 'g')
		define_img_colors(&cub->game.color, 0, color, 0);
	else if (door == 'b')
		define_img_colors(&cub->game.color, 0, 0, color);
	else if (door == 's')
		define_img_colors(&cub->game.color, color, color, color);
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
	if (rays[ray].vertical_hit)
		color = 200;
	else
		color = 250;
	shadow = floor((rays[ray].dist / 500) * 255);
	color -= shadow;
	if (color > 250)
		color = 250;
	else if (color < 0)
		color = 0;
	if (ft_isalpha(rays[ray].wall_content) && !(cub->game.is_texture))
		define_doors_color(rays[ray].wall_content, color, cub);
	else
		define_img_colors(&cub->game.color, color, color, color);
	if (cub->toggle.debug == TRUE)//|| !(cub->game.is_texture))
		toggle_debug_colors(&cub->game.color, rays, ray);
	if (cub->toggle.night_mode == TRUE)
		toggle_night_mode(&cub->game.color, rays, ray);
}
