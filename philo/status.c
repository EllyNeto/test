/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:09:20 by eneto             #+#    #+#             */
/*   Updated: 2024/11/28 15:12:25 by eneto            ###   ########.fr       */
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
	printf("%ld philo %d taken a fork.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
	pthread_mutex_lock(philo->right_fork);
	if (philo->status->end_actv == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	printf("%ld philo %d taken a fork.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
	philo->last_meal_time = ft_get_time_in_milis();
	philo->meals_counter++;
	ft_lock_f(philo);
	printf("%ld philo %d is eating.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
	usleep(philo->status->time_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
