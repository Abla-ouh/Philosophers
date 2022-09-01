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

void	lets_eat(t_args *philo)
{
	struct timeval	time_now;
	long			counter;

	counter = 0;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->message);
	printf("⏳%ld %d has taken a left fork🍴\n", get_current_time(counter), philo->index);
	pthread_mutex_unlock(&philo->message);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->message);
	printf("⏳%ld %d has taken a right fork🍴\n", get_current_time(philo->counter), philo->index);
	printf("⏳%ld %d is eating 🍝\n", get_current_time(philo->counter), philo->index);
	pthread_mutex_unlock(&philo->message);
	gettimeofday(&time_now, NULL);
	counter = time_now.tv_sec * 1000 + time_now.tv_usec / 1000;
	while (get_current_time(counter) < philo->time_to_eat)
		usleep(200);
	philo->last_meal = get_current_time(philo->counter);
	philo->number_of_times++;
}

void	*routini(void *philosoph)
{
	t_args *philo;

	philo = (t_args *)philosoph;
	while(1)
	{
		lets_eat(philo);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	return (NULL);
}

int 	born_threads(t_philo *philo)
{
	int i;
	i = 0;
	
	while (i < philo->args->nb_philo)
	{	
		if (!(philo->args[i].threads = malloc(sizeof(pthread_t))))
			return (0);
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

	philos->args = malloc(sizeof(t_args) * ft_atoi(av[1]));
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
        if (!check_args(av))
			return(printf("Error: invalid arguments\n"));
		if (!init_data(av, &philos))
			return(printf("Error\n"));
    }
    else
		return (printf("invalid arguments\n"));
    
    return (0);
}
