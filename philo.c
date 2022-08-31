/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:38:21 by abouhaga          #+#    #+#             */
/*   Updated: 2022/08/31 10:30:57 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int check_args(char **av)
{
    int i;
    
    i = 1;
    while(av[i])
    {
        if (check_number(av[i]) == 0)
            return (0);
    	i++;
    }
	return(1);
}

void	*routini(void *philo)
{
	t_args *philosoph;

	philosoph = (t_args *)philo;
	while(1)
	{
		pthread_mutex_lock(philosoph->l_fork);
		printf("Philosopher %d has taken left fork\n", philosoph->index);	
		pthread_mutex_lock(philosoph->r_fork);
		printf("Philosopher %d has taken right fork\n", philosoph->index);
		printf("Philosopher %d is eating\n", philosoph->index);
		usleep(philosoph->time_to_eat * 1000);
		printf("Philosopher %d is sleeping\n", philosoph->index);
		pthread_mutex_unlock(philosoph->l_fork);
		pthread_mutex_unlock(philosoph->r_fork);
		printf("Philosopher %d is sleeping\n", philosoph->index);
		usleep(philosoph->time_to_sleep * 1000);
		printf("Philosopher %d is thinking\n", philosoph->index);
	}
	
	return (NULL);
}

int 	born_threads(t_philo *philo)
{
	int i;
	i = 0;
	
	while (i < philo->args->nb_philo)
	{	
		philo->args[i].threads = malloc(sizeof(pthread_t));
		philo->args[i].index = i + 1;
		if (pthread_create(philo->args[i].threads, NULL, routini, &philo->args[i]) != 0)
		{
			printf("test");
			exit (1);
			printf("Error: pthread_create failed\n");
			return (0);
		}
		usleep(100);
		i++;
	}
	while(1)
		;
	return (1);
}

void init_forks(t_philo *philo)
{
	int i;
	i = 0;
	while(i < philo->args->nb_philo)
	{
		pthread_mutex_init(&(philo->forks[i]), NULL); 
		i++;
	}
	i = 0;
	while(i < philo->args->nb_philo)
	{
		philo->args[i].l_fork = &philo->forks[i];
		philo->args[i].r_fork = &philo->forks[(i + 1) % philo->args->nb_philo]; //when we do the modulo of number with another number greater thn it , we get the same number 
		i++;
	}
}

int init_data(char **av, t_philo *philos)
{
	int i;
	i = 1;

	philos->args = malloc(sizeof(t_args) * philos->args->nb_philo);
	philos->args[0].nb_philo = ft_atoi(av[1]);
	philos->args[0].time_to_die = ft_atoi(av[2]);
	philos->args[0].time_to_eat = ft_atoi(av[3]);
	philos->args[0].time_to_sleep = ft_atoi(av[4]);
	if(av[5])
		philos->args->nb_must_eat = ft_atoi(av[5]);
	else
		philos->args->nb_must_eat = 0; // must have eaten more thn 1
	if (philos->args[0].nb_philo < 0 || philos->args[0].time_to_die < 0
		|| philos->args[0].time_to_eat < 0|| philos->args[0].time_to_sleep < 0)
			return (0);
	while(i < philos->args->nb_philo)
	{
		philos->args[i].time_to_sleep = philos->args->time_to_sleep;
		philos->args[i].time_to_eat = philos->args->time_to_eat;
		philos->args[i].time_to_die = philos->args->time_to_die;
		philos->args[i].nb_must_eat = philos->args->nb_must_eat;
		i++;
	}
	init_forks(philos);
	if (!born_threads(philos))
	 	return (0);
	return (1);
}

int main(int ac, char **av)
{
	t_philo philos;
	
    if(ac == 5 || ac == 6)
    {
        if(!check_args(av))
        	return(printf("Error: invalid arguments\n"));
		if(!init_data(av, &philos))
			return(printf("Error\n"));
    }
    else
		return (printf("invalid arguments\n"));
    
    return (0);
}
