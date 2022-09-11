/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:51:06 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/08 15:33:25 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
#include <stdbool.h>

typedef struct s_args
{
	int		nb_philo;
	int		index;
	int		init_time;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_must_eat;
	bool	is_eating;
	bool	all_eaten_ntimes;
	pthread_mutex_t message;
	int		number_of_times;
	long	last_meal;
	pthread_t *threads;
	pthread_mutex_t	mutex_id;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
 } t_args;

typedef struct s_philo
{
	struct s_args	*args;
	pthread_mutex_t	*forks; //with malloc after
	
}			t_philo;

int		ft_atoi(const char *str);
long	get_current_time();
void	smart_print(char *message, t_args *philo, int p_id);
int		monitor(t_philo *philo);
void	ft_usleep(int ms_time);

#endif