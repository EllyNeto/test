/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:23:34 by eneto             #+#    #+#             */
/*   Updated: 2024/12/09 14:03:25 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (philo->forks)
	{
		pthread_mutex_destroy(philo->forks);
		free(philo->forks);
	}
	pthread_detach(philo->philos->thread);
	free(philo->philos);
	free(philo);
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
void	verify(t_philo *vrf)
{
	if (vrf->status->nbr_limit_meals != -1
		&& vrf->meals_counter >= vrf->status->nbr_limit_meals)
		vrf->full = 1;
}
