/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 00:21:19 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/11 11:06:44 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	nb;
	int				neg;

	i = 0;
	nb = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		nb = nb * 10 + str[i] - '0';
		if ((nb > 9223372036854775807) && (neg < 0))
			return (0);
		else if ((nb > 9223372036854775807) && (neg >= 0))
			return (-1);
		i++;
	}
	return (neg * nb);
}

long	get_current_time(void)
{
	struct timeval	time_now;
	long			millis_t;

	gettimeofday(&time_now, NULL);
	millis_t = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	return (millis_t);
}

void	ft_usleep(int ms_time)
{
	long start_time;
	start_time = get_current_time();
	while((get_current_time() - start_time ) < ms_time)
		usleep(300);
}

void smart_print(char *message, t_philo *philo, int p_id)
{
	int millis_t;

	sem_wait(philo->message);
	millis_t = get_current_time() - philo->init_time;
	printf(message, millis_t, p_id);
	sem_post(philo->message);
}