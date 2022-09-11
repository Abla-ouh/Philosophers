/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:27:25 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/11 18:19:36 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int ms_time)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < ms_time)
		usleep(300);
}

long	get_current_time(void)
{
	struct timeval	time_now;
	long			millis_t;

	gettimeofday(&time_now, NULL);
	millis_t = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	return (millis_t);
}

void	smart_print(char *message, t_args *philo, int p_id)
{
	int	millis_t;

	pthread_mutex_lock(&philo->message);
	millis_t = get_current_time() - philo->init_time;
	printf(message, millis_t, p_id);
	pthread_mutex_unlock(&philo->message);
}
