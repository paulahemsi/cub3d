/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:21:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/03/25 12:55:48 by phemsi-a         ###   ########.fr       */
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

/*
** scene configs
*/

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

typedef struct		s_map 
{
	unsigned int	total_column;
	unsigned int	total_row;
	char			**row;
}					t_map;

typedef	struct		s_configs
{
	unsigned int	window_width;
	unsigned int	window_height;
	t_paths			path;
	t_rgb			floor;
	t_rgb			ceiling;
	t_map			map;
}					t_configs;

/*
** mlx
*/

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void				parse_configs(t_configs	*configs, char *line);
void				parse_map(t_configs *configs, char *line);
void				return_error(int error_id);
void				set_map(t_configs *configs, char *line);
void				fill_map(t_configs *configs, char *file);
void				check_walls(t_configs *configs);
void				render_cub(t_configs *configs);

#endif
