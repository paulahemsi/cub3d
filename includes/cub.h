/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:21:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/02 23:36:37 by phemsi-a         ###   ########.fr       */
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

# define X				0
# define Y				1
# define PI				3.14159265358979323846
# define TILE_SIZE		64
# define PLAYER_HEIGHT	32
# define FOV			60 * (PI / 180)

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
	unsigned int	tile_size[2];
	char			**row;
}					t_map;

typedef struct		s_player
{
	int				plane_dist;
	int				pos[2];
	int				move_dir;
	int				turn_dir;
	int				radius;
	float			angle;
	float			delta_x;
	float			delta_y;
	int				speed;
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
	float			step;
	int				total;
	int				hor_col[2];
}					t_ray;

typedef	struct		s_configs
{
	unsigned int	width;
	unsigned int	height;
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
void				check_walls(t_configs *configs);
/*
** render cub
*/
void				render_cub(t_configs *configs);
void				render_minimap(t_data *img);
void				put_square(t_data *img, int pos_x, int pos_y, int color);
void				put_line(t_data *img, int *player_pos, int x2, int y2);
void				put_pixel(t_data *img, int pos_x, int pos_y, int color);
void				put_circle(t_data *img, int center_x, int center_y, int radius);
void				put_walls(t_data *img);

/*
** events
*/
int					mouse_clicked(int btn, int pos_x, int pos_y, t_data *img);
int					key_pressed(int key, t_data *img);
int					key_released(int key, t_data *img);
void				return_error(int error_id);
int					close_cub(int key, t_data *img);

#endif
