# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/05 21:18:02 by phemsi-a          #+#    #+#              #
#    Updated: 2021/05/10 23:49:21 by phemsi-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a
MLX = libmlx.a

LIBFT_PATH = ./libraries/libft/
MLX_PATH = ./libraries/minilibx-linux/

SRC = ./source/mandatory/
PARSE = $(SRC)parse_scene/
RENDER = $(SRC)render_cub/
SYSTEM = $(SRC)system/

SRC_BONUS = ./source/bonus/
PARSE_BONUS = $(SRC_BONUS)parse_scene/
RENDER_BONUS = $(SRC_BONUS)render_cub/
SYSTEM_BONUS = $(SRC_BONUS)system/

FILES = $(SRC)cub.c $(SYSTEM)free.c $(SYSTEM)save_bmp.c $(SYSTEM)events.c $(SYSTEM)error.c $(PARSE)parse_scene.c $(PARSE)parse_settings.c $(PARSE)parse_map.c $(PARSE)check_map.c $(PARSE)load_textures.c $(RENDER)render_cub.c $(RENDER)render_tools.c $(RENDER)put_line.c $(RENDER)put_background.c $(RENDER)render_utils.c $(RENDER)raycasting.c $(RENDER)collisions.c $(RENDER)put_walls.c $(RENDER)put_sprites.c $(RENDER)check_tile_and_limits.c
OBJECTS = cub.o free.o error.o parse_settings.o parse_map.o check_map.o render_cub.o events.o render_tools.o put_line.o put_background.o render_utils.o raycasting.o put_walls.o save_bmp.o load_textures.o put_sprites.o collisions.o parse_scene.o check_tile_and_limits.o

BONUS_FILES = $(SRC_BONUS)cub_b.c $(SYSTEM_BONUS)free_b.c $(SYSTEM_BONUS)save_bmp_b.c $(SYSTEM_BONUS)events_b.c $(SYSTEM_BONUS)error_b.c $(PARSE_BONUS)parse_scene_b.c $(PARSE_BONUS)parse_settings_b.c $(PARSE_BONUS)parse_map_b.c $(PARSE_BONUS)check_map_b.c $(PARSE_BONUS)load_textures_b.c $(RENDER_BONUS)render_cub_b.c $(RENDER_BONUS)render_tools_b.c $(RENDER_BONUS)put_line_b.c $(RENDER_BONUS)render_minimap_b.c $(RENDER_BONUS)put_background_b.c $(RENDER_BONUS)put_hud_b.c $(RENDER_BONUS)render_utils_b.c $(RENDER_BONUS)raycasting_b.c $(RENDER_BONUS)collisions_b.c $(RENDER_BONUS)put_walls_b.c $(RENDER_BONUS)put_sprites_b.c $(RENDER_BONUS)background_gradient_b.c $(RENDER_BONUS)night_vision_b.c $(RENDER_BONUS)wall_color_b.c $(RENDER_BONUS)check_tile_b.c
BONUS_OBJECTS = cub_b.o free_b.o error_b.o parse_settings_b.o parse_map_b.o check_map_b.o render_cub_b.o events_b.o render_tools_b.o put_line_b.o render_minimap_b.o put_background_b.o render_utils_b.o raycasting_b.o put_walls_b.o save_bmp_b.o load_textures_b.o put_sprites_b.o collisions_b.o parse_scene_b.o background_gradient_b.o night_vision_b.o put_hud_b.o wall_color_b.o check_tile_b.o

CC = clang
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lm -lbsd -lmlx -lXext -lX11
RE = rm -f

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	@echo making cub3D
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -L $(LIBFT_PATH) -L $(MLX_PATH) -lft $(MLX_FLAGS)
	@echo ___________________________________  
	@echo "|" _____ "|"   "|" ___ "|" ___ ___ "|" "|"   "|" "|"
	@echo "|" "|"   "|" "|"_"|" "|"__ "|" "|"_"|" __"|"____ "|" "|" "|" "|"
	@echo "|" "|" "|" "|"_________"|"__ "|"______ "|"___"|"_"|" "|"
	@echo "|" "|"_"|"   "|" _______ "|"______ "|"   "|" ____"|"
	@echo "|" ___ "|" "|"____ "|" "|"______ "|" "|"_"|" "|"____ "|"
	@echo "|"___"|"_"|"____ "|" "|"   ___ "|" "|"________ "|" "|"
	@echo "|"   ________"|" "|" "|"__ "|" "|"______ "|" "|" "|" "|"
	@echo "|" "|" "|" ________"|" "|" __"|"____ "|" "|" "|" __"|" "|"
	@echo "|"_"|" "|"__ "|"   "|" __"|"__ "|" ____"|" "|" "|"_"|" __"|"
	@echo "|"   ____"|" "|" "|"____ "|" "|"__ "|"   "|"__ "|"__ "|"
	@echo "|" "|"_______"|"_______"|"___"|"___"|"___"|"_____"|"
	@echo done! Have fun!

bonus: $(BONUS_OBJECTS) $(LIBFT) $(MLX)
	@echo making cub3D
	@$(CC) $(CFLAGS) -g -o cub3D $(BONUS_OBJECTS) -L $(LIBFT_PATH) -L $(MLX_PATH) -lft $(MLX_FLAGS)
	@echo ___________________________________  
	@echo "|" _____ "|"   "|" ___ "|" ___ ___ "|" "|"   "|" "|"
	@echo "|" "|"   "|" "|"_"|" "|"__ "|" "|"_"|" __"|"____ "|" "|" "|" "|"
	@echo "|" "|" "|" "|"_________"|"__ "|"______ "|"___"|"_"|" "|"
	@echo "|" "|"_"|"   "|" _______ "|"______ "|"   "|" ____"|"
	@echo "|" ___ "|" "|"____ "|" "|"______ "|" "|"_"|" "|"____ "|"
	@echo "|"___"|"_"|"____ "|" "|"   ___ "|" "|"________ "|" "|"
	@echo "|"   ________"|" "|" "|"__ "|" "|"______ "|" "|" "|" "|"
	@echo "|" "|" "|" ________"|" "|" __"|"____ "|" "|" "|" __"|" "|"
	@echo "|"_"|" "|"__ "|"   "|" __"|"__ "|" ____"|" "|" "|"_"|" __"|"
	@echo "|"   ____"|" "|" "|"____ "|" "|"__ "|"   "|"__ "|"__ "|"
	@echo "|" "|"_______"|"_______"|"___"|"___"|"___"|"_____"|"
	@echo done! Have fun!

$(MLX):
	@echo making minilibx....
	@echo -----------------------------------------
	@make --no-print-directory -C $(MLX_PATH)
	@echo -----------------------------------------
	@echo done!

$(LIBFT):
	@echo making libft....
	@make --no-print-directory -C $(LIBFT_PATH) $(LIBFT)
	@echo done!

$(OBJECTS): $(FILES)
	@$(CC) $(CFLAGS) -g -c $(FILES)

$(BONUS_OBJECTS): $(BONUS_FILES)
	@$(CC) $(CFLAGS) -g -c $(BONUS_FILES)

clean:
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	@make --no-print-directory -C $(MLX_PATH) clean
	$(RM) $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	@echo cleaning!
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	@echo done!
	
re: fclean all 

.PHONY: all clean fclean re 
