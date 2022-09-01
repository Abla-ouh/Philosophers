/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:27:25 by abouhaga          #+#    #+#             */
/*   Updated: 2022/08/31 07:58:51 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	get_current_time(long start)
{
	struct timeval	time_now;
	long			counter;

	gettimeofday(&time_now, NULL);
	counter = time_now.tv_sec * 1000 + time_now.tv_usec / 1000;
	return (counter - start);
}