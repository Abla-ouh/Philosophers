/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:46:17 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/11 22:38:17 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_number(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	int		status;
	int		reswait;

	status = 0;
	reswait = 0;
	if (ac == 1)
		return (0);
	if (check_args(av) && (ft_atoi(av[1]) > 0 && (ac == 5 || ac == 6)))
	{
		philos = init_data(av);
		if (!philos)
			return (printf("Error\n"));
		create_process(philos);
		while (reswait != -1 && status == 0)
			reswait = waitpid(-1, &status, 0);
		if (status != 0)
			kill_left(philos);
		sem_close(philos->message);
		sem_close(philos->forks);
	}
	else
		return (printf("invalid arguments\n"));
	return (0);
}
