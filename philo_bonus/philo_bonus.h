/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:21:29 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/12 22:24:47 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_philo
{
	pid_t	pid;
	int		nb_philo;
	int		index;
	long	init_time;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_must_eat;
	sem_t	*bns_sem;
	sem_t	*last_meal_sem;
	sem_t	*message;
	sem_t	*forks;
	long	last_meal;
	int		number_of_times;
}	t_philo;

t_philo	*init_data(char **av);
void	create_process(t_philo *philo);
void	ft_usleep(int ms_time);
int		ft_atoi(const char *str);
long	get_current_time(void);
void	smart_print(char *message, t_philo *philo, int p_id);
void	kill_left(t_philo *philo);

#endif