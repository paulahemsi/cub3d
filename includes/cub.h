/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:21:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/30 23:53:03 by phemsi-a         ###   ########.fr       */
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

# define X			0
# define Y			1

# define ESC		0xff1b
# define LEFT		0xff51
# define UP			0xff52
# define RIGHT		0xff53
# define DOWN		0xff54
# define W			0x0077
# define A			0x0061
# define S			0x0073
# define D			0x0064
# define SPACE		0x0020
# define TAB		0xff09
# define SHIFT		0xffe1
# define MOUSE_1	1
# define MOUSE_2	2
# define MOUSE_3	3

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
	int				pos[2];
	int				dir[2];
	// int				speed;
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

typedef	struct		s_configs
{
	unsigned int	width;
	unsigned int	height;
	t_paths			path;
	t_rgb			floor;
	t_rgb			ceiling;
	t_map			map;
	t_player		player;
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

void				parse_configs(t_configs	*configs, char *line);
void				parse_map(t_configs *configs, char *line);
void				parse_map_size(t_configs *configs, char *line);
void				fill_map(t_configs *configs, char *file);
void				check_walls(t_configs *configs);
void				render_cub(t_configs *configs);
void				put_square(t_data *img, int pos_x, int pos_y, int color);
void				put_pixel(t_data *img, int pos_x, int pos_y, int color);
int					mouse_clicked(int btn, int pos_x, int pos_y, t_data *img);
int					key_pressed(int key, t_data *img);
void				return_error(int error_id);

#endif
