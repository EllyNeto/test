/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:09:20 by eneto             #+#    #+#             */
/*   Updated: 2024/11/25 16:01:07 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_think(t_philo *philo)
{
	printf("Philo %d is thinking.\n", philo->id);
	usleep(500);
}

void	t_sleep(t_philo *philo)
{
	printf("Philo %d is sleeping.\n", philo->id);
	usleep(philo->status->time_sleep * 1000);
}

void	t_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	philo->last_meal_time = ft_get_time_in_milis();
	philo->meals_counter++;
	printf("Philo %d is eathing.\n", philo->id);
	usleep(philo->status->time_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

