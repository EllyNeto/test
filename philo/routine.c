/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:08:50 by eneto             #+#    #+#             */
/*   Updated: 2024/11/19 16:13:12 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *m)
{
	t_philo	*philo;
	
	philo = (t_philo *)m;
	while (1)
	{
		printf("[%ld] philo[%d] is eating\n", ft_time_diff(philo->mode->start_actv), philo->id);
		usleep(philo->mode->time_eat * 1e3);
		printf("[%ld] philo[%d] is sleeping\n", ft_time_diff(philo->mode->start_actv), philo->id);
		usleep(philo->mode->time_sleep * 1e3);
		printf("[%ld] philo[%d] is thinking\n", ft_time_diff(philo->mode->start_actv), philo->id);
	}
    return (NULL);
}

int		start_routine(t_mode *mode)
{
	int i;

	i = -1;
	while(mode->philo_nbr > ++i)
		pthread_create(&mode->philos[i].thread, NULL, routine, &mode->philos[i]);
	i = -1;
	while(mode->philo_nbr > ++i)
		pthread_join(mode->philos[i].thread , NULL);
	return (0);
}