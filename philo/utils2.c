/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:29:47 by eneto             #+#    #+#             */
/*   Updated: 2024/12/12 08:23:32 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_wtf(t_philo *philo)
{
	pthread_mutex_lock(&philo->status->end_actv_lock);
	if (philo->status->end_actv == 0)
	{
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		pthread_mutex_lock(&philo->status->actv_lock);
		printf("%ld philo %d taken a fork.\n",
			ft_time_diff(philo->status->start_actv), philo->id);
		pthread_mutex_unlock(&philo->status->actv_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->status->end_actv_lock);
	return ;
}

void	ft_wie(t_philo *philo)
{
	pthread_mutex_lock(&philo->status->end_actv_lock);
	if (philo->status->end_actv == 0)
	{
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		pthread_mutex_lock(&philo->status->actv_lock);
		printf("%ld philo %d is eating.\n",
			ft_time_diff(philo->status->start_actv), philo->id);
		pthread_mutex_unlock(&philo->status->actv_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->status->end_actv_lock);
	return ;
}

void	ft_sleep(long time_in_ms, t_philo *philo)
{
	long	start;

	start = ft_get_time_in_milis();
	while ((ft_get_time_in_milis() - start) < time_in_ms)
	{
		pthread_mutex_lock(&philo->status->end_actv_lock);
		if (philo->status->end_actv == 1)
		{
			pthread_mutex_unlock(&philo->status->end_actv_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->status->end_actv_lock);
		usleep(100);
	}
}

void	ft_ini_f(t_status *status)
{
	int	i;

	i = 0;
	while (status->philo_nbr > i)
	{
		if (status->philos[i].id % 2 == 0)
		{
			status->philos[i].left_fork = &status->forks[i];
			status->philos[i].right_fork = &status->forks[(i + 1)
				% status->philo_nbr];
		}
		else
		{
			status->philos[i].right_fork = &status->forks[i];
			status->philos[i].left_fork = &status->forks[(i + 1)
				% status->philo_nbr];
		}
		i++;
	}
}
