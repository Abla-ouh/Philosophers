/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:14:23 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/09 18:19:50 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void philo_routine(t_philo *philo, int i)
{
    philo->index = i;
    while(philo->nb_must_eat == -1 || )
    {
        
    }
    
}

void    create_process(t_philo *philo)
{
    pid_t   pid;
    int     i;

    i = 0;
    while(i < philo->nb_philo)
    {
        pid = fork();
        if (pid == 0)
            philo_routine(philo, i);
        else if (pid < 0)
            return (printf("Error: fork failed\n"));
        i += 2;
    }
    i = 1;
    while(i < philo->nb_philo)
    {
        pid = fork();
        if (pid == 0)
            philo_routine(philo, i);
        else if (pid < 0)
            return (printf("Error: fork failed\n"));
        i += 2;
    }
}