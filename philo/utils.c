/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:23:34 by eneto             #+#    #+#             */
/*   Updated: 2024/12/11 09:04:16 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	verify(t_philo *vrf)
{
	if (vrf->status->nbr_limit_meals != -1
		&& vrf->meals_counter >= vrf->status->nbr_limit_meals)
		vrf->full = 1;
}

long	ft_get_time_in_milis(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	ft_time_diff(long time)
{
	return (ft_get_time_in_milis() - time);
}

long	ft_atol(char *str)
{
	long	n;
	long	sg;

	n = 0;
	sg = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sg = -1;
	while (*str >= 48 && *str <= 57)
		n = n * 10 + *(str++) - '0';
	return (n * sg);
}

void	ft_free_all(t_status *philo)
{
	int	i;

	i = 0;
	if (philo->forks)
	{
		while (i < philo->philo_nbr)
			pthread_mutex_destroy(&philo->forks[i++]);
	}
	pthread_mutex_destroy(&philo->end_actv_lock);
	pthread_mutex_destroy(&philo->actv_lock);
	pthread_mutex_destroy(&philo->lock);
	free(philo->forks);
	free(philo->philos);
	free(philo);
}
