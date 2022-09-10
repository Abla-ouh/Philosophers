/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:21:29 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/10 12:03:02 by abouhaga         ###   ########.fr       */
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

void	create_process(t_philo *philo);
void	ft_usleep(int ms_time);
int		ft_atoi(const char *str);
long	get_current_time(void);
void	smart_print(char *message, t_philo *philo, int p_id, sem_t *sem_msg);

#endif