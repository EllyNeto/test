/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:08:50 by eneto             #+#    #+#             */
/*   Updated: 2024/11/25 16:12:32 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *m)
{
	t_philo	*philo;

	philo = (t_philo *)m;
	while (philo->meals_counter < philo->status->nbr_limit_meals)
	{
		t_eat(philo);
		t_sleep(philo);
		t_think(philo);
	}
	return (NULL);
}
void	v_status(t_status *status)
{
	int	i;

	i = 0;
	while (i < status->philo_nbr)
	{
		if (ft_time_diff(status->philos[i].last_meal_time) > status->time_die)
		{
			printf("Philo %d is dead.\n", status->philos[i].id);
			status->end_actv = 1;
			return ;
		}
		i++;
	}
}

int	start_routine(t_status *status)
{
	int i;

	i = -1;
	while (status->philo_nbr > ++i)
		pthread_create(&status->philos[i].thread, NULL, routine,
			&status->philos[i]);
	while(status->end_actv == 0)
	{
		v_status(status);
		usleep(500);
	}
	i = -1;
	while (status->philo_nbr > ++i)
		pthread_join(status->philos[i].thread, NULL);
	return (0);
}