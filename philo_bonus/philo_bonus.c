/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:46:17 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/09 17:10:56 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int init_data(char **av, t_philo *philos)
{
	int i;
	i = 1;
    
    sem_unlink("forks");
    philos[0].forks = sem_open("forks", O_CREAT, 0644, philos->nb_philo);
    if (philos[0].forks == SEM_FAILED)
    {
        return(printf("Error: sem_open failed\n"));
        exit(1);
    }
    sem_unlink("message");
    philos[0].message = sem_open("message", O_CREAT, 0644, 1);
    if (philos[0].message == SEM_FAILED)
    {
        return(printf("Error: sem_open failed\n"));
        exit(1);
    }
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philos[0].nb_philo = ft_atoi(av[1]);
	philos[0].time_to_die = ft_atoi(av[2]);
	philos[0].time_to_eat = ft_atoi(av[3]);
	philos[0].time_to_sleep = ft_atoi(av[4]);
	if(av[5])
		philos->nb_must_eat = ft_atoi(av[5]);
	else
		philos->nb_must_eat = -1; // must have eaten more thn 1
	if (philos[0].nb_philo < 0 || philos[0].time_to_die < 0
		|| philos[0].time_to_eat < 0|| philos[0].time_to_sleep < 0)
			return (0);
	while(i < philos->nb_philo)
	{
        philos[i].forks = philos[0].forks;
        philos[i].message = philos[0].message;
		philos[i].time_to_sleep = philos->time_to_sleep;
		philos[i].time_to_eat = philos->time_to_eat;
		philos[i].time_to_die = philos->time_to_die;
		philos[i].nb_must_eat = philos->nb_must_eat;
		i++;
	}
	philos->all_eaten_ntimes = 0;
	return (1);
}

int main(int ac, char **av)
{
	t_philo philos;
    sem_t *forks;
	
    if(ac == 5 || ac == 6)
    {
        if (!check_args(av))
			return(printf("Error: invalid arguments\n"));
		if (!init_data(av, &philos))
			return(printf("Error\n"));
        create_process(&philos);
        
    }
    else
		return (printf("invalid arguments\n"));
    return (0);
}