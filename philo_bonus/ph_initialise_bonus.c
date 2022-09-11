/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_initialise_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:46:58 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/11 20:19:44 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sems(char **av, t_philo *philos)
{
	sem_unlink("forks");
	philos[0].forks = sem_open("forks", O_CREAT, 0644, philos->nb_philo);
	if (philos[0].forks == SEM_FAILED)
	{
		printf("Error: sem_open failed\n");
		exit(1);
	}
	sem_unlink("message");
	philos[0].message = sem_open("message", O_CREAT, 0644, 1);
	if (philos[0].message == SEM_FAILED)
	{
		printf("Error: sem_open failed\n");
		exit(1);
	}
	sem_unlink("bns_sem");
	philos[0].bns_sem = sem_open("bns_sem", O_CREAT, 0644, 1);
	philos[0].time_to_die = ft_atoi(av[2]);
	philos[0].time_to_eat = ft_atoi(av[3]);
	philos[0].time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philos->nb_must_eat = ft_atoi(av[5]);
	else
		philos->nb_must_eat = -1;
}

t_philo	*init_data(char **av)
{
	int		i;
	t_philo	*philos;

	i = 1;
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philos[0].nb_philo = ft_atoi(av[1]);
	init_sems(av, philos);
	if (philos[0].nb_philo < 0 || philos[0].time_to_die < 0
		|| philos[0].time_to_eat < 0 || philos[0].time_to_sleep < 0)
		return (0);
	while (i < philos->nb_philo)
	{
		philos[i].forks = philos->forks;
		philos[i].message = philos->message;
		philos[i].nb_philo = philos->nb_philo;
		philos[i].time_to_sleep = philos->time_to_sleep;
		philos[i].time_to_eat = philos->time_to_eat;
		philos[i].time_to_die = philos->time_to_die;
		philos[i].nb_must_eat = philos->nb_must_eat;
		i++;
	}
	return (philos);
}
