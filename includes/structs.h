/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:26:04 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/28 15:59:29 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdint.h>
/*
** game
*/
typedef struct s_map
{
	unsigned int	total_column;
	unsigned int	total_row;
	char			**row;
}					t_map;

typedef struct s_player
{
	int				plane_dist;
	int				pos[2];
	int				direction[3];
	float			angle;
	int				speed;
	float			rotate_speed;
	int				height;
	int				invisible;
}					t_player;

typedef struct s_ray
{
	float			angle;
	float			hit[2];
	float			dist;
	int				vertical_hit;
	int				up;
	int				left;
	float			step;
	int				total;
	char			wall_content;
	int				sprite_hitted;
}					t_ray;

typedef struct s_cast
{
	float			intercept[2];
	float			step[2];
	int				hitted;
	float			hit[2];
	float			distance;
	char			content;
	int				sprite_hitted;
}					t_cast;

typedef struct s_rgb
{
	int				red;
	int				green;
	int				blue;
}					t_rgb;

typedef struct s_gradient
{
	t_rgb			increment;
	t_rgb			color_distance;
}					t_gradient;

typedef struct s_toggle
{
	int				gradient;
	int				debug;
	int				night_mode;
	int				show_minimap;
	int				always_running;
	int				save;
	int				bmp_id;
}					t_toggle;
/*
** mlx
*/
typedef struct s_data
{
	void			*ptr;
	char			*data;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;
/*
** scene settings
*/
typedef struct s_settings
{
	int				screen[2];
	int				world[2];
	int				center[2];
	char			*path[5];
	t_rgb			floor;
	t_rgb			ceiling;
}					t_settings;

typedef struct s_texture
{
	t_data			img;
	int				width;
	int				height;
}					t_texture;

typedef struct s_sprite
{
	t_texture		texture;
	int				pos[2];
	float			angle;
	int				height;
	int				width;
	float			distance;
	float			init[2];
	float			end[2];
	int				visible;
}					t_sprite;

typedef struct s_render
{
	t_map			map;
	t_player		player;
	t_ray			ray;
	t_rgb			color;
	t_texture		*texture;
	t_sprite		*sprites;
	t_texture		hud;
	t_texture		skybox;
	int				num_sprites;
	int				wall_height;
	int				is_texture;
	int				sprite;
	int				wall;
	int				offset[2];
}					t_render;

typedef struct s_cub
{
	void			*mlx_ptr;
	void			*window_ptr;
	t_data			img;
	t_settings		settings;
	t_toggle		toggle;
	t_render		game;
}					t_cub;
/*
** aux
*/
typedef struct s_bresenham
{
	int				delta[2];
	int				increment[2][2];
	int				longest;
	int				shortest;
	int				numerator;
	int				i;
}					t_bresenham;
/*
** bmp
*/
typedef struct s_bmp_header
{
	uint16_t		type;
	uint32_t		size;
	uint16_t		reserved;
	uint32_t		offset;
	uint32_t		dib_header_size;
	int32_t			width_px;
	int32_t			height_px;
	uint16_t		num_planes;
	uint16_t		bits_per_pixel;
	uint32_t		compression;
	uint32_t		image_size_bytes;
	int32_t			x_resolution_ppm;
	int32_t			y_resolution_ppm;
	uint32_t		num_colors;
	uint32_t		important_colors;
}					t_bmp_header;

#endif
