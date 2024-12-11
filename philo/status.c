/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:09:20 by eneto             #+#    #+#             */
/*   Updated: 2024/12/11 09:05:41 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->status->end_actv_lock);
	if (philo->status->end_actv == 0)
	{
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		pthread_mutex_lock(&philo->status->actv_lock);
		printf("%ld philo %d is thinking.\n",
			ft_time_diff(philo->status->start_actv), philo->id);
		pthread_mutex_unlock(&philo->status->actv_lock);
	}
	else
		pthread_mutex_unlock(&philo->status->end_actv_lock);
}

void	t_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->status->end_actv_lock);
	if (philo->status->end_actv == 0)
	{
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		pthread_mutex_lock(&philo->status->actv_lock);
		printf("%ld philo %d is sleeping.\n",
			ft_time_diff(philo->status->start_actv), philo->id);
		pthread_mutex_unlock(&philo->status->actv_lock);
	}
	else
		pthread_mutex_unlock(&philo->status->end_actv_lock);
	usleep(philo->status->time_sleep * 1000);
}

void	t_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_wtf(philo);
	pthread_mutex_lock(philo->right_fork);
	ft_wtf(philo);
	pthread_mutex_lock(&philo->status->lock);
	philo->last_meal_time = ft_get_time_in_milis();
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->status->lock);
	verify(philo);
	ft_wie(philo);
	usleep(philo->status->time_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}
