/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_kill_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:43:27 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/11 18:47:39 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_left(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[i].nb_philo)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}
