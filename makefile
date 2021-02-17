# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/24 09:53:36 by wperu             #+#    #+#              #
#    Updated: 2020/10/24 14:42:52 by wperu            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d.a

MINILIBX = minilibx-linux/libmlx.a

MINILIBX_MAKE = make -C minilibx-linux

SRCS 	= ft_check_error.c \
		ft_error.c \
		ft_key.c \
		ft_parcing.c \
		ft_save.c \
		ft_texture.c \
		ft_utils.c \
		ft_utils2.c \
		ft_raycast.c \
		ft_utils3.c \
		ft_close.c \
		ft_wall.c \
		ft_sprites.c \
		ft_init.c \
		get_next_line.c \
		get_next_line_utils.c

BOBJS	= ${SRCS:.c=.o}

OBJS	= ${SRCS:.c=.o}

INCLUDE	= cub.h

CC		= gcc

CFLAGS  = -Wall -Wextra -Werror

RM      = rm -f

$(NAME):    $(OBJS)  $(INCLUDE)
			$(MINILIBX_MAKE)
			cp minilibx-linux/libmlx.a ./$(NAME)
			ar rcs $(NAME) $(OBJS) $(INCLUDE)
			$(CC) $(CFLAGS) main_cub.c cub3d.a -L minilibx-linux -lmlx -lXext -lX11 -lm -o cub3d 

%.o: %.c
	     $(CC) -I includes/ -o $@ -c $< $(CFLAGS)

all: $(NAME) $(INCLUDE)

bonus: all

clean:
		$(RM) $(OBJS)
		make clean -C minilibx-linux/

fclean:		clean	
			$(RM) $(NAME)
			make clean -C minilibx-linux/

runsave: all
		./cub3d test.cub --save

run:	all
		./cub3d test.cub

.PHONY:	all clean fclean re bonus runsave run