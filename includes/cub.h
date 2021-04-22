/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:21:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/22 16:27:06 by phemsi-a         ###   ########.fr       */
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
# define NORTH			0
# define SOUTH			1
# define EAST			2
# define WEST			3
# define SPRITE			4
# define CEILING		0
# define FLOOR			1
# define FRONT			0
# define MOVE			0
# define SIDE			1
# define TURN			2
# define WIDTH			0
# define HEIGHT			1
# define TOP			0
# define BOTTOM			1


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
# define Q				0x0071
# define E				0x0065
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
** game
*/
typedef struct		s_map
{
	unsigned int	total_column;
	unsigned int	total_row;
	char			**row;
}					t_map;

typedef struct		s_player
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

typedef struct		s_ray
{
	float			angle;
	float			hit[2];
	float			dist;
	int				vertical_hit;
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

typedef struct		s_rgb
{
	int				red;
	int				green;
	int				blue;
}					t_rgb;

typedef struct		s_gradient
{
	t_rgb			increment;
	t_rgb			color_distance;
}					t_gradient;

typedef struct		s_toggle
{
	int				gradient;
	int				debug;
	int				night_mode;
	int				save;
	int				show_minimap;
	int				bmp_id;
}					t_toggle;
/*
** mlx
*/
typedef struct		s_data
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
typedef	struct		s_settings
{
	int				screen[2];
	int				world[2];
	int				center[2];
	char			*path[5];
	t_rgb			floor;
	t_rgb			ceiling;
}					t_settings;

typedef struct		s_texture
{
	t_data			img;
	int				width;
	int				height;
}					t_texture;

typedef struct		s_sprite
{
	t_texture		texture;
	int				pos[2];
	float			angle;
	int				height;
	int				width;
}					t_sprite;

typedef struct		s_render
{
	t_map			map;
	t_player		player;
	t_ray			ray;
	t_rgb			color;
	t_texture		*texture;
	t_sprite		*sprites;
	t_texture		hearts;
	int				num_sprites;
	int				wall_height;
	int				is_texture;
	int				wall;
	int				offset[2];
}					t_render;

typedef struct		s_cub
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
	uint16_t		type;//0x4d42
	uint32_t		size;//bytes
	uint16_t		reserved;
	//uint16_t		reserved2;
	uint32_t		offset;//54 bytes
	uint32_t		dib_header_size;//(40 bytes)
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
/*
** parse configs
*/
void				parse_configs(t_cub *cub, char *line);
void				parse_map(t_settings *configs, char *line);
void				parse_map_size(t_map *map, char *line);
void				fill_map(t_cub *cub, char *file, int row);
void				check_map(t_render *game);

/*
** render cub
*/
void				render_cub(t_cub *cub);
void				save_bmp(t_cub *cub);
void				render_minimap(t_cub *cub, t_map *map, t_ray *rays);
void				raycasting(t_cub *cub, t_ray *rays);
void				put_background(t_cub *cub);
void				put_walls(t_cub *cub, t_ray *rays);
void				put_sprites(t_cub *cub, t_sprite *sprite, t_player *player);
void				load_textures(char **path, t_cub *cub, t_render *game);
/*
** render tools
*/
int					color_picker(unsigned char red, unsigned char green, unsigned char blue);
void				put_square(t_data *img, int pos_x, int pos_y, int color);
void				put_line(t_cub *cub, int *pos, int x2, int y2);
void				put_pixel(t_data *img, int pos_x, int pos_y, int color);
void				put_circle(t_data *img, int center_x, int center_y, int radius);
/*
** render utils
*/
void				define_img_colors(t_rgb *color, int red, int green, int blue);
float				normalize_angle(float angle);
int					is_tile_free(float *pos, t_settings *set, t_map *map, int secret_door);
float				calc_distance(int *pos, float *hit);
/*
** events
*/
int					mouse_clicked(int btn, int pos_x, int pos_y, t_data *img);
int					key_pressed(int key, t_cub *cub);
int					key_released(int key, t_cub *cub);
void				return_error(int error_id);
int					close_cub(int key, t_cub *cub);
/*
** init and free
*/
void				free_all(t_cub *cub);
void				free_cub(t_cub *cub);
void				free_paths(char **path);
void				init_cub(t_cub *cub);

#endif
