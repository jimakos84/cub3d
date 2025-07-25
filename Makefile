# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvlachos <dvlachos@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 09:58:38 by dvlachos          #+#    #+#              #
#    Updated: 2025/07/25 12:39:30 by dvlachos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := cub3d
CFLAGS  := -Wextra -Wall -Werror
LIBMLX  := ./MLX42
LIBFT   := ./libft
HEADERS := -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS    := $(LIBMLX)/build/libmlx42.a -L $(LIBFT) -lft -ldl -lglfw -pthread -lm
SRCS    := src/main.c src/validation.c

OBJS    := ${SRCS:.c=.o}

all: check_mlx libft libmlx $(NAME)

check_mlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "MLX42 not found. Cloning..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

libmlx: check_mlx
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	$(MAKE) -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft check_mlx

