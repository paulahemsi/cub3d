/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:21:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/05/01 01:34:08 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./defines.h"
# include "./structs.h"
# include "../../libraries/libft/libft.h"
# include "../../libraries/minilibx-linux/mlx.h"
# include "../../libraries/minilibx-linux/mlx_int.h"

/*
** parse configs
*/
void	parse_scene(char *file, t_cub *cub);
void	parse_settings(t_cub *cub, char *line);
void	parse_map(t_settings *configs, char *line);
void	parse_map_size(t_map *map, char *line);
void	fill_map(t_cub *cub, char *file, int row);
void	check_map(t_cub *cub, t_render *game);
/*
** render cub
*/
void	render_cub(t_cub *cub);
void	save_bmp(t_cub *cub);
void	raycasting(t_cub *cub, t_ray *rays);
void	put_background(t_cub *cub, t_rgb *ceiling, t_rgb *floor, t_rgb *color);
void	put_walls(t_cub *cub, t_ray *rays);
void	put_sprite(t_sprite *sprites, t_player *player, t_cub *cub, t_ray *ray);
void	load_textures(char **path, t_cub *cub, t_render *game);
void	find_vertical_collision(t_cub *cub, t_cast *vertical, float angle);
void	find_horizontal_collision(t_cub *cub, t_cast *horizontal, float angle);
/*
** render tools
*/
void	put_line(t_cub *cub, int *pos, int x2, int y2);
int		color_picker(unsigned char red, unsigned char green, unsigned char blue);
void	define_img_colors(t_rgb *color, int red, int green, int blue);
void	put_pixel(t_data *img, int pos_x, int pos_y, int color);
/*
** check tile and limits
*/
int		has_wall(float *pos, t_settings *set, t_map *map);
int		is_tile_free(float *pos, t_settings *set, t_map *map, int secret_door);
int		is_inside_world_limits(float *coord, int *world);
int		is_inside_screen(int *screen, float x, float y);
/*
** render utils
*/
float	hit_distance(int *pos, float *hit);
float	define_distance(int *pos1, int *pos2);
float	normalize_angle(float angle);
int		is_ray_facing(int direction, float angle);
/*
** system and events
*/
int		key_pressed(int key, t_cub *cub);
int		key_released(int key, t_cub *cub);
void	return_error(t_cub *cub, int error_id);
int		close_cub(t_cub *cub);
void	free_cub(t_cub *cub);
void	free_paths(char **path);

#endif
