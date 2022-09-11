# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 23:44:54 by abouhaga          #+#    #+#              #
#    Updated: 2022/09/11 19:54:59 by abouhaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread -g

SRCS = philo_bonus.c bonus_process.c bonus_utils.c \
		ph_initialise_bonus.c ph_kill_bonus.c 

NAME = philo_bonus

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)  -o $(NAME)

clean :

fclean : clean
	rm -f $(NAME) 

re : fclean all

.PHONY : all clean fclean re