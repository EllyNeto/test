/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:09:20 by eneto             #+#    #+#             */
/*   Updated: 2024/12/04 18:44:05 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_think(t_philo *philo)
{
	if (philo->status->end_actv == 1)
		return ;
	printf("%ld philo %d is thinking.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
}

void	t_sleep(t_philo *philo)
{
	if (philo->status->end_actv == 1)
		return ;
	printf("%ld philo %d is sleeping.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
	usleep(philo->status->time_sleep * 1000);
}

void	limit_meals(t_status *meals_l)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (++i < meals_l->philo_nbr)
	{
		if (meals_l->philos[i].full == 1)
			j++;
		if (j == meals_l->philo_nbr)
			meals_l->end_actv = 1;
	}
	return ;
}

void	ft_lock_f(t_philo *lock)
{
	if (lock->status->end_actv == 1)
	{
		pthread_mutex_unlock(lock->right_fork);
		pthread_mutex_unlock(lock->left_fork);
		return ;
	}
}

void	t_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->status->end_actv == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	ft_wtf(philo);
	pthread_mutex_lock(philo->right_fork);
	if (philo->status->end_actv == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	ft_wtf(philo);
	philo->last_meal_time = ft_get_time_in_milis();
	philo->meals_counter++;
	verify(philo);
	ft_lock_f(philo);
	ft_wie(philo);
	usleep(philo->status->time_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return ;
}
