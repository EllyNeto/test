/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:09:20 by eneto             #+#    #+#             */
/*   Updated: 2024/12/06 16:09:12 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_think(t_philo *philo)
{
	if (philo->status->end_actv == 1)
		return ;
	pthread_mutex_lock(&philo->status->end_actv_lock);
	if (philo->status->end_actv == 0)
	{
		printf("%ld philo %d is thinking.\n",
			ft_time_diff(philo->status->start_actv), philo->id);
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->status->end_actv_lock);
}

void	t_sleep(t_philo *philo)
{
	if (philo->status->end_actv == 1)
		return ;
	pthread_mutex_lock(&philo->status->end_actv_lock);
	if (philo->status->end_actv == 0)
	{
		printf("%ld philo %d is sleeping.\n",
			ft_time_diff(philo->status->start_actv), philo->id);
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->status->end_actv_lock);
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
	pthread_mutex_lock(&lock->status->end_actv_lock);
	if (lock->status->end_actv == 1)
	{
		pthread_mutex_unlock(&lock->status->end_actv_lock);
		pthread_mutex_unlock(lock->left_fork);
		pthread_mutex_unlock(lock->right_fork);
		return ;
	}
	pthread_mutex_unlock(&lock->status->end_actv_lock);
}

void	t_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->status->end_actv_lock);
	/*if (philo->status->end_actv == 1)
	{
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}*/
	pthread_mutex_unlock(&philo->status->end_actv_lock);
	ft_wtf(philo);
	pthread_mutex_lock(philo->right_fork);
	//ft_lock_f(philo);
	ft_wtf(philo);
	pthread_mutex_lock(&philo->status->end_actv_lock);
	philo->last_meal_time = ft_get_time_in_milis();
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->status->end_actv_lock);
	verify(philo);
	//ft_lock_f(philo);
	ft_wie(philo);
	usleep(philo->status->time_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}
