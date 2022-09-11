/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_initi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:09:46 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/11 21:41:19 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->nb_philo)
	{
		pthread_mutex_init(&(philo->forks[i]), NULL);
		i++;
	}
	i = 0;
	while (i < philo->args->nb_philo)
	{
		philo->args[i].l_fork = &philo->forks[i];
		philo->args[i].r_fork = &philo->forks[(i + 1) % philo->args->nb_philo];
		i++;
	}
}

void	init_struct_var(t_philo *philos)
{
	int	i;

	i = 1;
	while (i < philos->args->nb_philo)
	{
		philos->args[i].time_to_sleep = philos->args->time_to_sleep;
		philos->args[i].time_to_eat = philos->args->time_to_eat;
		philos->args[i].time_to_die = philos->args->time_to_die;
		philos->args[i].nb_must_eat = philos->args->nb_must_eat;
		i++;
	}
}

int	init_data(char **av, t_philo *philos)
{
	int	i;

	i = 1;
	philos->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	philos->args = malloc(sizeof(t_args) * ft_atoi(av[1]));
	philos->args[0].nb_philo = ft_atoi(av[1]);
	philos->args[0].time_to_die = ft_atoi(av[2]);
	philos->args[0].time_to_eat = ft_atoi(av[3]);
	philos->args[0].time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philos->args->nb_must_eat = ft_atoi(av[5]);
	else
	philos->args->nb_must_eat = -1;
	if (philos->args[0].nb_philo < 0 || philos->args[0].time_to_die < 0
		|| philos->args[0].time_to_eat < 0 || philos->args[0].time_to_sleep < 0)
		return (0);
	init_struct_var(philos);
	philos->args->all_eaten_ntimes = 0;
	init_forks(philos);
	if (!born_threads(philos))
		return (0);
	return (1);
}
