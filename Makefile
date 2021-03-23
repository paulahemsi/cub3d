# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/05 21:18:02 by phemsi-a          #+#    #+#              #
#    Updated: 2021/03/23 16:51:15 by phemsi-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft.a

SRC = ./source/
PRINT = ./source/parsing_identifiers/print_
LIBFT_PATH = ./libraries/libft/

FILES = cub.c error.c parse_configs.c parse_map.c check_walls.c
OBJECTS = $(FILES:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror
RE = rm -f

all: $(NAME)

$(LIBFT):
	@echo making libft....
	@make --no-print-directory -C $(LIBFT_PATH) $(LIBFT)
	@echo done!

$(NAME): $(OBJECTS) $(LIBFT)
	@echo making cub3D
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) -L $(LIBFT_PATH) -lft
	@echo done! Have fun!

$(OBJECTS): $(FILES)
	@echo making objects....
	@$(CC) $(FLAGS) -c $(FILES)
	@echo done!

test: $(OBJECTS) $(LIBFT)
	@echo making cub3D
	@$(CC) $(FLAGS) -fsanitize=leak -o $(NAME) $(OBJECTS) -L $(LIBFT_PATH) -lft
	@echo done! Have fun!

clean:
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	$(RM) $(OBJECTS)

fclean: clean
	@echo cleaning!
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	@echo done!
	
re: fclean all 

.PHONY: all clean fclean re 
