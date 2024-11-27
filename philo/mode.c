/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:09:20 by eneto             #+#    #+#             */
/*   Updated: 2024/11/27 13:15:41 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_think(t_philo *philo)
{
	printf("%ld philo %d is thinking.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
}

void	t_sleep(t_philo *philo)
{
	printf("%ld philo %d is sleeping.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
	usleep(philo->status->time_sleep * 1000);
}

void	t_eat(t_philo *philo)
{
	//pthread_mutex_t	meal_lock;

	//pthread_mutex_init(&meal_lock, NULL);
	pthread_mutex_lock(philo->left_fork);
	printf("%ld philo %d taken a fork.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%ld philo %d taken a fork.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
	//pthread_mutex_lock(&meal_lock);
	philo->last_meal_time = ft_get_time_in_milis();
	philo->meals_counter++;
	//pthread_mutex_unlock(&meal_lock);
	printf("%ld philo %d is eathing.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
	usleep(philo->status->time_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
