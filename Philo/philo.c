/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:38:21 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/10 15:04:14 by abouhaga         ###   ########.fr       */
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

void	ft_usleep(int ms_time)
{
	long start_time;
	start_time = get_current_time();
	while((get_current_time() - start_time ) < ms_time)
		usleep(300);
}

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
	if(philo->nb_must_eat != -1)
	{
		pthread_mutex_lock(&philo->mutex_id);
		philo->number_of_times++;
		pthread_mutex_unlock(&philo->mutex_id);
	}
}

void	*routini(void *philosoph)
{
	t_args *philo;

	philo = (t_args *)philosoph;

	while(philo->nb_must_eat == - 1 || !philo->all_eaten_ntimes)
	{
		lets_eat(philo);
		if (philo->all_eaten_ntimes)
			return (NULL);
		smart_print("⏳ %d ms %d is sleeping 😴\n", philo, philo->index);
		ft_usleep(philo->time_to_sleep);
		smart_print("⏳ %d ms %d is thinking 🤔\n", philo, philo->index);
	}
	return (NULL);
}

int 	born_threads(t_philo *philo)
{
	int i;
	int init_time;

	i = 0;
	init_time = get_current_time();
	while (i < philo->args->nb_philo)
	{
		if (!(philo->args[i].threads = malloc(sizeof(pthread_t))))
			return (0);
		philo->args[i].index = i + 1;
		philo->args[i].init_time = init_time;
		philo->args[i].last_meal = get_current_time();
		if (pthread_create(philo->args[i].threads, NULL, routini, &philo->args[i]) != 0)
		{
			printf("Error: pthread_create failed\n");
			return (0);
		}
		usleep(100);
		i++;
	}
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
		philo->args[i].r_fork = &philo->forks[(i + 1) % philo->args->nb_philo];
		i++;
	}
}

int init_data(char **av, t_philo *philos)
{
	int i;
	i = 1;

	philos->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	philos->args = malloc(sizeof(t_args) * ft_atoi(av[1]));
	philos->args[0].nb_philo = ft_atoi(av[1]);
	philos->args[0].time_to_die = ft_atoi(av[2]);
	philos->args[0].time_to_eat = ft_atoi(av[3]);
	philos->args[0].time_to_sleep = ft_atoi(av[4]);
	if(av[5])
		philos->args->nb_must_eat = ft_atoi(av[5]);
	else
		philos->args->nb_must_eat = -1; // must have eaten more thn 1
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
	philos->args->all_eaten_ntimes = 0;
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
        if (!check_args(av))
			return(printf("Error: invalid arguments\n"));
		if (!init_data(av, &philos))
			return(printf("Error\n"));
		if (monitor(&philos))
			return (1);
    }
    else
		return (printf("invalid arguments\n"));
    return (0);
}
