# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/05 21:18:02 by phemsi-a          #+#    #+#              #
#    Updated: 2021/04/30 15:22:21 by phemsi-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a
MLX = libmlx.a

SRC = ./source/
PARSE = $(SRC)parse_scene/
RENDER = $(SRC)render_cub/
SYSTEM = $(SRC)system/
LIBFT_PATH = ./libraries/libft/
MLX_PATH = ./libraries/minilibx-linux/

FILES = $(SRC)cub.c $(SYSTEM)free.c $(SYSTEM)save_bmp.c $(SYSTEM)events.c $(SYSTEM)error.c $(PARSE)parse_scene.c $(PARSE)parse_settings.c $(PARSE)parse_map.c $(PARSE)check_map.c $(PARSE)load_textures.c $(RENDER)render_cub.c $(RENDER)render_tools.c $(RENDER)put_line.c $(RENDER)render_minimap.c $(RENDER)put_background.c $(RENDER)put_hud.c $(RENDER)render_utils.c $(RENDER)raycasting.c $(RENDER)collisions.c $(RENDER)put_walls.c $(RENDER)put_sprites.c $(RENDER)background_gradient.c $(RENDER)night_vision.c $(RENDER)debug_mode.c $(RENDER)check_tile_and_limits.c
OBJECTS = cub.o free.o error.o parse_settings.o parse_map.o check_map.o render_cub.o events.o render_tools.o put_line.o render_minimap.o put_background.o render_utils.o raycasting.o put_walls.o save_bmp.o load_textures.o put_sprites.o collisions.o parse_scene.o background_gradient.o night_vision.o put_hud.o debug_mode.o check_tile_and_limits.o
BONUS_FILES =
BONUS_OBJECTS =

CC = clang
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lm -lbsd -lmlx -lXext -lX11
RE = rm -f

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	@echo making cub3D
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) -L $(LIBFT_PATH) -L $(MLX_PATH) -lft $(MLX_FLAGS)
	@echo done! Have fun!
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

bonus: $(OBJECTS) $(BONUS_OBJECTS) $(LIBFT) $(MLX)
	@echo making cub3D
	@$(CC) $(FLAGS) -g -fsanitize=leak -o $(NAME) $(OBJECTS) $(BONUS_OBJECTS) -L $(LIBFT_PATH) -L $(MLX_PATH) -lft $(MLX_FLAGS)
	@echo done! Have fun!
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
	@$(CC) $(FLAGS) -g -c $(FILES)

$(BONUS_OBJECTS): $(BONUS_FILES)
	@$(CC) $(FLAGS) -g -c $(BONUS_FILES)

clean:
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	@make --no-print-directory -C $(MLX_PATH) clean
	$(RM) $(OBJECTS)

fclean: clean
	@echo cleaning!
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	@echo done!
	
re: fclean all 

.PHONY: all clean fclean re 
