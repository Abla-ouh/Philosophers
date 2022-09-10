/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 23:30:01 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/10 00:19:30 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *ph_routine(void *philo)
{
    t_philo *ph;
    
    ph = (t_philo *)philo;
    while(!ph->done_eating)
    {
        if(get_current_time() - ph->last_meal >= ph->time_to_die && !ph->is_eating)
            exit(1);
    }
    return (NULL);
}

void    lets_eat_bns(t_philo *philo)
{
    pthread_t  thread;
    pthread_create(&thread, NULL, &ph_routine, philo);
    sem_wait(philo->forks);
    smart_print("%d ms %d has taken a fork\n", philo, philo->index + 1, philo->message);
    sem_wait(philo->forks);
    smart_print("%d ms %d has taken a fork\n", philo, philo->index + 1, philo->message);
    philo->last_meal = get_current_time();
    philo->is_eating = 1;
    smart_print("%d ms %d is eating 🍝\n", philo, philo->index + 1, philo->message);
    ft_usleep(philo->time_to_eat);
    sem_post(philo->forks);
    sem_post(philo->forks);
}
void philo_routine(t_philo *philo, int i)
{
    philo->index = i;
    while(philo->nb_must_eat == -1 || philo->nb_must_eat--)
    {
        lets_eat_bns(philo);
        philo->is_eating = 0;
        smart_print("%d ms %d is sleeping\n", philo, philo->index + 1, philo->message);
        ft_usleep(philo->time_to_sleep);
        smart_print("%d ms %d is thinking\n", philo, philo->index + 1, philo->message);
    }
    philo->done_eating = 1;
    sem_close(philo->message);
    sem_close(philo->forks);
    exit(0);
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