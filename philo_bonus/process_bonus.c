/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 23:30:01 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/12 22:06:59 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ph_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->number_of_times = 0;
	while (philo->nb_must_eat == -1
		|| philo->number_of_times < philo->nb_must_eat)
	{
		sem_wait(philo->forks);
		smart_print("%d ms %d has taken a fork\n", philo, philo->index + 1);
		sem_wait(philo->forks);
		smart_print("%d ms %d has taken a fork\n", philo, philo->index + 1);
		sem_wait(philo->last_meal_sem);
		philo->last_meal = get_current_time();
		sem_post(philo->last_meal_sem);
		smart_print("%d ms %d is eating 🍝\n", philo, philo->index + 1);
		if (philo->nb_must_eat != -1)
			philo->number_of_times++;
		ft_usleep(philo->time_to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		smart_print("%d ms %d is sleeping\n", philo, philo->index + 1);
		ft_usleep(philo->time_to_sleep);
		smart_print("%d ms %d is thinking\n", philo, philo->index + 1);
	}
	exit (0);
}

void	to_do(t_philo *philo, int i)
{
	pthread_t	thread;
	long		spent_time;

	sem_wait(philo->bns_sem);
	philo->index = i;
	sem_post(philo->bns_sem);
	philo->last_meal = get_current_time();
	pthread_create(&thread, NULL, ph_routine, philo);
	while (4814)
	{
		sem_wait(philo->last_meal_sem);
		spent_time = get_current_time() - philo->last_meal;
		sem_post(philo->last_meal_sem);
		if (spent_time >= philo->time_to_die)
		{
			sem_wait(philo->message);
			printf("%ld ms %d is dead\n", get_current_time() - philo->init_time,
				philo->index + 1);
			exit (1);
		}
	}
	exit(1);
}

int	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Error: fork failed");
		exit(1);
	}
	return (pid);
}

void	create_process(t_philo *philo)
{
	pid_t	pid;
	int		i;
	long	init_time;

	i = 0;
	init_time = get_current_time();
	while (i < philo->nb_philo)
	{
		philo[i].init_time = init_time;
		pid = ft_fork();
		if (pid == 0)
			to_do(philo, i);
		if (pid != 0)
			philo[i].pid = pid;
		i++;
	}
}
