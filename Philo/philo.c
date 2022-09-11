/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:38:21 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/11 20:16:16 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lets_eat(t_args *philo)
{
	pthread_mutex_lock(philo->l_fork);
	smart_print("⏳ %d ms %d has taken a fork🍴\n", philo, philo->index);
	pthread_mutex_lock(philo->r_fork);
	smart_print("⏳ %d ms %d has taken a fork 🍴\n", philo, philo->index);
	philo->last_meal = get_current_time();
	philo->is_eating = 1;
	smart_print("⏳ %d ms %d is eating 🍝\n", philo, philo->index);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->is_eating = 0;
	if (philo->nb_must_eat != -1)
	{
		pthread_mutex_lock(&philo->mutex_id);
		philo->number_of_times++;
		pthread_mutex_unlock(&philo->mutex_id);
	}
}

void	*routini(void *philosoph)
{
	t_args	*philo;

	philo = (t_args *)philosoph;
	philo->number_of_times = 0;
	while (philo->nb_must_eat == -1 || !philo->all_eaten_ntimes)
	{
		lets_eat(philo);
		smart_print("⏳ %d ms %d is sleeping 😴\n", philo, philo->index);
		ft_usleep(philo->time_to_sleep);
		smart_print("⏳ %d ms %d is thinking 🤔\n", philo, philo->index);
	}
	return (NULL);
}

int	born_threads(t_philo *philo)
{
	int	i;
	int	init_time;

	i = 0;
	init_time = get_current_time();
	while (i < philo->args->nb_philo)
	{
		philo->args[i].threads = malloc(sizeof(pthread_t));
		if (!philo->args[i].threads)
			return (0);
		philo->args[i].index = i + 1;
		philo->args[i].init_time = init_time;
		philo->args[i].last_meal = get_current_time();
		if (pthread_create(philo->args[i].threads, NULL,
				routini, &philo->args[i]) != 0)
		{
			printf("Error: pthread_create failed\n");
			return (0);
		}
		usleep(100);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	philos;

	if (ac == 5 || ac == 6)
	{
		if (!check_args(av))
			return (printf("Error: invalid arguments\n"));
		if (!init_data(av, &philos))
			return (printf("Error\n"));
		if (monitor(&philos))
			return (1);
	}
	else
		return (printf("invalid arguments\n"));
	return (0);
}
