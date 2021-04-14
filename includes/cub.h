/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:21:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/14 04:05:05 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libraries/libft/libft.h"
# include "../libraries/minilibx-linux/mlx.h"
# include "../libraries/minilibx-linux/mlx_int.h"
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdint.h>

# define X				0
# define Y				1
# define ROW			1
# define COL			0
# define HOR			0
# define VER			1
# define CEILING		0
# define FLOOR			1
# define FRONT			0
# define SIDE			1
# define TILE_SIZE		64
# define HALF_TILE		32
# define PLAYER_HEIGHT	32
# define SCALE			0.1
# define TOGGLE			-1
/*
** maths
*/
# define PI				3.14159265
# define TWO_PI			6.28316530
# define FOV			60 * (PI / 180)
# define HALF_FOV		FOV / 2
/*
** events
*/
# define ESC			0xff1b
# define LEFT			0xff51
# define UP				0xff52
# define RIGHT			0xff53
# define DOWN			0xff54
# define W				0x0077
# define A				0x0061
# define S				0x0073
# define D				0x0064
# define G				0x0067
# define B				0x0062
# define P				0x0070
# define N				0x006e
# define SPACE			0x0020
# define TAB			0xff09
# define SHIFT			0xffe1
# define MOUSE_1		1
# define MOUSE_2		2
# define MOUSE_3		3
# define KEYPRESS		2
# define KEYRELEASE		3
# define CLIENTMESSAGE	33
# define KEYPRESS_MASK	1L<<0
# define KEYREL_MASK	1L<<1
# define NOTIFY_MASK	1L<<17

/*
** scene configs
*/
typedef struct		s_map
{
	unsigned int	total_column;
	unsigned int	total_row;
	char			**row;
	int				show_minimap;
	//float			scale;
}					t_map;

typedef struct		s_player
{
	int				plane_dist;
	int				pos[2];
	//int				map_pos[2];
	int				radius;
	int				turn_dir;
	int				move_dir;
	int				side_dir;
	int				direction[2];
	float			angle;
	int				speed;
	float			rotate_speed;
	int				height;
	int				invisible;
	//float			delta_x;
	//float			delta_y;
}					t_player;

typedef struct		s_paths
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
}					t_paths;

typedef struct		s_rgb
{
	int				red;
	int				green;
	int				blue;
}					t_rgb;

typedef struct		s_ray
{
	float			angle;
	float			hit[2];
	float			dist;
	int				vertical_hit;
	int				hor_col[2];
	int				up;
	int				left;
	float			step;
	int				total;//resolution width
	char			wall_content;
}					t_ray;

typedef struct		s_cast
{
	float			intercept[2];
	float			step[2];
	int				hitted;
	float			hit[2];
	float			distance;
	char			content;
}					t_cast;

typedef struct		s_gradient
{
	t_rgb			increment;
	t_rgb			color_distance;
}					t_gradient;

typedef	struct		s_configs
{
	unsigned int	screen_width;
	unsigned int	screen_height;
	unsigned int	world_width;
	unsigned int	world_height;
	int				center[2];
	int				gradient;
	int				debug;
	int				night_mode;
	int				save;
	int				bmp_id;
	t_paths			path;
	t_rgb			floor;
	t_rgb			ceiling;
	t_map			map;
	t_player		player;
	t_ray			ray;
}					t_configs;
/*
** mlx
*/
typedef struct		s_data
{
	void			*mlx_ptr;
	void			*window_ptr;
	void			*ptr;
	char			*data;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_configs		*cub;
	t_rgb			c;
}					t_data;
/*
** aux
*/
typedef struct		s_bresenham
{
	int delta[2];
	int increment[2][2];
	int longest;
	int shortest;
	int numerator;
	int i;
}					t_bresenham;
/*
** bmp
*/
typedef struct		s_bmp_header
{
	uint16_t		type;// Magic identifier: 0x4d42
	uint32_t		size;// File size in bytes
	uint16_t		reserved;// Not used
	//uint16_t		reserved2;// Not used
	uint32_t		offset;// Offset to image data in bytes from beginning of file (54 bytes)
	uint32_t		dib_header_size;// DIB Header size in bytes (40 bytes)
	int32_t			width_px;// Width of the image
	int32_t			height_px;// Height of image
	uint16_t		num_planes;// Number of color planes
	uint16_t		bits_per_pixel;// Bits per pixel
	uint32_t		compression;// Compression type
	uint32_t		image_size_bytes;// Image size in bytes
	int32_t			x_resolution_ppm;// Pixels per meter
	int32_t			y_resolution_ppm;// Pixels per meter
	uint32_t		num_colors;// Number of colors  
	uint32_t		important_colors;
}					t_bmp_header;
/*
** parse configs
*/
void				parse_configs(t_configs	*configs, char *line);
void				parse_map(t_configs *configs, char *line);
void				parse_map_size(t_configs *configs, char *line);
void				fill_map(t_configs *cub, char *file, int row);
void				check_map(t_configs *configs);
/*
** render cub
*/
void				render_cub(t_configs *cub);
void				save_bmp(t_data *img);
void				render_minimap(t_data *img, t_ray *rays);
void				raycasting(t_data *img, t_configs *cub, t_ray *rays);
void				put_background(t_data *img, t_configs *cub);
void				put_walls(t_data *img, t_ray *rays);
/*
** render tools
*/
int					color_picker(unsigned char red, unsigned char green, unsigned char blue);
void				put_square(t_data *img, int pos_x, int pos_y, int color);
void				put_line(t_data *img, int *pos, int x2, int y2);
void				put_pixel(t_data *img, int pos_x, int pos_y, int color);
void				put_circle(t_data *img, int center_x, int center_y, int radius);
/*
** render utils
*/
void				define_img_colors(t_data *img, int red, int green, int blue);
float				normalize_angle(float angle);
int					is_tile_free(float *pos, t_configs *cub, int secret_door);
float				calc_distance(int *pos, float *hit);
/*
** events
*/
int					mouse_clicked(int btn, int pos_x, int pos_y, t_data *img);
int					key_pressed(int key, t_data *img);
int					key_released(int key, t_data *img);
void				return_error(int error_id);
int					close_cub(int key, t_data *img);
void				free_cub(t_configs *cub);
void				free_all(t_data *img);
void				init_cub(t_configs *cub);

#endif
