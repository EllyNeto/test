/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:08:50 by eneto             #+#    #+#             */
/*   Updated: 2024/12/12 08:04:37 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_onephilo(t_philo *philo)
{
	if (philo->status->philo_nbr == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_wtf(philo);
		usleep(philo->status->time_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	return (0);
}

void	*ft_routine(void *m)
{
	t_philo	*philo;

	philo = (t_philo *)m;
	if (ft_onephilo(philo) == 1)
		return (NULL);
	while (1)
	{
		t_eat(philo);
		t_sleep(philo);
		t_think(philo);
		pthread_mutex_lock(&philo->status->end_actv_lock);
		if (philo->status->end_actv)
			return (pthread_mutex_unlock(&philo->status->end_actv_lock), NULL);
		pthread_mutex_unlock(&philo->status->end_actv_lock);
	}
	return (NULL);
}

void	v_status(t_status *status)
{
	int	i;

	i = 0;
	while (status->philo_nbr > i)
	{
		pthread_mutex_lock(&status->lock);
		if (ft_time_diff(status->philos[i].last_meal_time) > status->time_die)
		{
			pthread_mutex_unlock(&status->lock);
			pthread_mutex_lock(&status->end_actv_lock);
			status->end_actv = 1;
			pthread_mutex_unlock(&status->end_actv_lock);
			pthread_mutex_lock(&status->actv_lock);
			printf("%ld philo %d died.\n", ft_time_diff(status->start_actv),
				status->philos[i].id);
			pthread_mutex_unlock(&status->actv_lock);
			return ;
		}
		pthread_mutex_unlock(&status->lock);
		i++;
	}
}

int	ft_start_routine(t_status *status)
{
	int	i;

	i = 0;
	while (status->philo_nbr > i)
	{
		if (pthread_create(&status->philos[i].thread, NULL, ft_routine,
				&status->philos[i]))
			return (1);
		i++;
	}
	while (status->end_actv != 1)
	{
		usleep(1000);
		v_status(status);
		limit_meals(status);
	}
	i = 0;
	while (status->philo_nbr > i)
	{
		if (pthread_join(status->philos[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}
