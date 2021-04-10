# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/05 21:18:02 by phemsi-a          #+#    #+#              #
#    Updated: 2021/04/10 03:42:18 by phemsi-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a
MLX = libmlx.a

SRC = ./source/
CONFIGS = $(SRC)parse_configs/
RENDER = $(SRC)render_cub/
LIBFT_PATH = ./libraries/libft/
MLX_PATH = ./libraries/minilibx-linux/

FILES = $(SRC)cub.c $(CONFIGS)error.c $(CONFIGS)parse_configs.c $(CONFIGS)parse_map.c $(CONFIGS)check_map.c $(RENDER)render_cub.c $(SRC)events.c $(RENDER)render_tools.c $(RENDER)put_line.c $(RENDER)render_minimap.c $(RENDER)put_background.c $(RENDER)utils.c $(RENDER)raycasting.c $(RENDER)put_walls.c
OBJECTS = cub.o error.o parse_configs.o parse_map.o check_map.o render_cub.o events.o render_tools.o put_line.o render_minimap.o put_background.o utils.o raycasting.o put_walls.o

CC = clang
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lm -lbsd -lmlx -lXext -lX11
RE = rm -f

all: $(NAME)

$(NAME): $(OBJECTS)
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

$(OBJECTS): $(FILES) $(LIBFT) $(MLX)
	$(CC) $(FLAGS) -g -c $(FILES)

test: $(OBJECTS)
	@echo making cub3D
	$(CC) $(FLAGS) -g -fsanitize=leak -o $(NAME) $(OBJECTS) -L $(LIBFT_PATH) -L $(MLX_PATH) -lft $(MLX_FLAGS)
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
