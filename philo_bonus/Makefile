# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 23:44:54 by abouhaga          #+#    #+#              #
#    Updated: 2022/09/09 23:48:39 by abouhaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo_bonus.c monitor_bonus.c bonus_process.c

NAME = philo_bonus

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)  -o $(NAME)

clean :

fclean : clean
	rm -f $(NAME) 

re : fclean all

.PHONY : all clean fclean re