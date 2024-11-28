/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:08:50 by eneto             #+#    #+#             */
/*   Updated: 2024/11/27 16:29:16 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *m)
{
	t_philo	*philo;

	philo = (t_philo *)m;
	if (philo->id % 2)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->status->end_actv_lock);
		if (philo->status->end_actv)
			return (pthread_mutex_unlock(&philo->status->end_actv_lock), NULL);
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		t_eat(philo);
		pthread_mutex_lock(&philo->status->end_actv_lock);
		if (philo->status->end_actv)
			return (pthread_mutex_unlock(&philo->status->end_actv_lock), NULL);
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		t_sleep(philo);
		pthread_mutex_lock(&philo->status->end_actv_lock);
		if (philo->status->end_actv)
			return (pthread_mutex_unlock(&philo->status->end_actv_lock), NULL);
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		t_think(philo);
	}
	return (NULL);
}

void	v_status(t_status *status)
{
	int	i;

	i = 0;
	while (i < status->philo_nbr)
	{
		if (ft_time_diff(status->philos[i].last_meal_time) > status->time_die)
		{
			printf("%ld philo %d is dead.\n", ft_time_diff(status->start_actv),
				status->philos[i].id);
			pthread_mutex_lock(&status->end_actv_lock);
			status->end_actv = 1;
			pthread_mutex_unlock(&status->end_actv_lock);
			return ;
		}
		i++;
	}
}

int	ft_start_routine(t_status *status)
{
	int	i;

	i = 0;
	while (status->philo_nbr > i)
	{
		pthread_create(&status->philos[i].thread, NULL, ft_routine,
			&status->philos[i]);
		i++;
	}
	while (status->end_actv != 1)
	{
		usleep(500);
		v_status(status);
	}
	i = -1;
	while (status->philo_nbr > ++i)
		pthread_join(status->philos[i].thread, NULL);
	return (0);
}
