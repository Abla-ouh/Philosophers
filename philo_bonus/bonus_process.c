/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 23:30:01 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/10 15:11:31 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *ph_routine(void *ph)
{
    t_philo *philo;
    philo = (t_philo *)ph;
    
    while(1)
    {
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
        philo->is_eating = 0;
        smart_print("%d ms %d is sleeping\n", philo, philo->index + 1, philo->message);
        ft_usleep(philo->time_to_sleep);
        smart_print("%d ms %d is thinking\n", philo, philo->index + 1, philo->message);
    }
    philo->done_eating = 1;
    sem_close(philo->message);
    sem_close(philo->forks);
}

// void    lets_eat_bns(t_philo *philo)
// {
//     t_philo *ph;
    
//     ph = (t_philo *)philo;
//     while(!ph->done_eating)
//     {
//         if(get_current_time() - ph->last_meal >= ph->time_to_die && !ph->is_eating)
//             exit(1);
//     }
//     return (NULL);
// }
void to_do(t_philo *philo, int i)
{
    pthread_t  thread;

    philo->index = i;
    pthread_create(&thread, NULL, &ph_routine, philo);
    while (1)
    {
        
    }
}

int ft_fork(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        printf("Error: fork failed");
        exit(1);
    }
    return (pid);
}

void create_process(t_philo *philo)
{
    pid_t   pid;
    int     i;
    int     init_time;

    i = 0;
    init_time = get_current_time();
    while(i < philo->nb_philo)
    {
        philo[i].init_time = init_time;
        pid = ft_fork();
        if (pid == 0)
            to_do(philo, i);
        i++;
    }
    
}