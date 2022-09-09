/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:21:29 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/09 23:06:28 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

typedef struct s_philo
{
	int		nb_philo;
	int		index;
	int		init_time;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_must_eat;
	bool	is_eating;
	bool	done_eating;
	sem_t   *message;
	sem_t   *forks;
	int		number_of_times;
	long	last_meal;
 } t_philo;

void    create_process(t_philo *philo);
#endif