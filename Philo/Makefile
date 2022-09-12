# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 07:51:14 by abouhaga          #+#    #+#              #
#    Updated: 2022/09/12 21:40:06 by abouhaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo.c ph_utils.c ph_monitor.c \
		ph_initi.c ph_parser.c 

NAME = philo

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)  -o $(NAME)

clean :

fclean : clean
	rm -f $(NAME) 

re : fclean all

.PHONY : all clean fclean re