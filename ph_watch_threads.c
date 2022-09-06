/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_watch_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:01:56 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/06 18:37:30 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int done_eating(t_philo *ph)
{
    int i;

    i = 0;
    while (i < ph->args->nb_philo)
    {
        if (ph->args->nb_must_eat == -1 || ph->args->nb_must_eat > ph->args->number_of_times)
            return (1);
        i++;
    }
    //ph->args->done_eating = 1;
    return (0);
}

int check_time(t_philo *philo)
{
    if ((get_current_time() - philo->args->last_meal) >= philo->args->time_to_die)
    {
        pthread_mutex_lock(&philo->args->message);
        smart_print("💀 %d ms %d died 💀\n", philo->args, philo->args->index);
        return (1);
    }
    return (0);
}

int monitor(t_philo *philo)
{
    while(done_eating(philo))
    {
        if (check_time(philo))
            return (1);
        usleep(300);
    }
    return (0);
}

