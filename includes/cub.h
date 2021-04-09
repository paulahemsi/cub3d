/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:21:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/09 17:27:34 by phemsi-a         ###   ########.fr       */
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

# define X				0
# define Y				1
# define ROW			1
# define COL			0
# define HOR			0
# define VER			1
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
# define SPACE			0x0020
# define TAB			0xff09
# define SHIFT			0xffe1
# define MOUSE_1		1
# define MOUSE_2		2
# define MOUSE_3		3

/*
** scene configs
*/

typedef struct		s_map
{
	unsigned int	total_column;
	unsigned int	total_row;
	//unsigned int	tile_size[2];
	char			**row;
	int				show_minimap;
}					t_map;

typedef struct		s_player
{
	int				plane_dist;
	int				pos[2];
	//int				map_pos[2];
	int				radius;
	int				turn_dir;
	int				move_dir;
	float			angle;
	int				speed;
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


typedef	struct		s_configs
{
	unsigned int	screen_width;
	unsigned int	screen_height;
	unsigned int	world_width;
	unsigned int	world_height;
	int				center[2];
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
** parse configs
*/
void				parse_configs(t_configs	*configs, char *line);
void				parse_map(t_configs *configs, char *line);
void				parse_map_size(t_configs *configs, char *line);
void				fill_map(t_configs *configs, char *file);
void				check_map(t_configs *configs);
/*
** render cub
*/
void				render_cub(t_configs *configs);
void				render_minimap(t_data *img, t_ray *rays);
void				raycasting(t_data *img, t_configs *cub, t_ray *rays);
void				put_background(t_data *img);
int					color_picker(unsigned char red, unsigned char green, unsigned char blue);
/*
** render tools
*/
void				put_square(t_data *img, int pos_x, int pos_y, int color);
void				put_line(t_data *img, int *player_pos, int x2, int y2);
void				put_pixel(t_data *img, int pos_x, int pos_y, int color);
void				put_circle(t_data *img, int center_x, int center_y, int radius);
/*
** render utils
*/
void				define_img_colors(t_data *img, int red, int green, int blue);
float				normalize_angle(float angle);
int					is_tile_free(float *pos, t_configs *cub);
float				calc_distance(int *pos, float *hit);

/*
** events
*/
int					mouse_clicked(int btn, int pos_x, int pos_y, t_data *img);
int					key_pressed(int key, t_data *img);
int					key_released(int key, t_data *img);
void				return_error(int error_id);
int					close_cub(int key, t_data *img);

#endif
