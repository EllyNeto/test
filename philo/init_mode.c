/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:24:30 by eneto             #+#    #+#             */
/*   Updated: 2024/12/09 13:46:04 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_mtx(t_status *mtx)
{
	int	i;

	i = 0;
	while (mtx->philo_nbr > i)
	{
		pthread_mutex_init(&mtx->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&mtx->end_actv_lock, NULL);
	pthread_mutex_init(&mtx->philos->meal_lock, NULL);
	return ;
}

int	ft_malloc_philos(t_status *status)
{
	int	i;

	i = 0;
	status->philos = malloc(sizeof(t_philo) * status->philo_nbr);
	ft_init_mtx(status);
	if (status->philos == NULL)
		return (1);
	while (status->philo_nbr > i)
	{
		status->philos[i].id = i + 1;
		status->philos[i].meals_counter = 0;
		status->philos[i].last_meal_time = status->start_actv;
		status->philos[i].full = 0;
		if ((i + 1) % 2 == 0)
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
		status->philos[i].status = status;
		i++;
	}
	return (0);
}

int	ft_malloc_struct(t_status *status, char **argv)
{
	status->philo_nbr = ft_atol(argv[1]);
	status->time_die = ft_atol(argv[2]);
	status->time_eat = ft_atol(argv[3]);
	status->time_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		status->nbr_limit_meals = ft_atol(argv[5]);
	else
		status->nbr_limit_meals = -1;
	status->start_actv = ft_get_time_in_milis();
	status->end_actv = 0;
	if ((argv[5] != NULL && status->nbr_limit_meals < 0)
		|| status->philo_nbr <= 0 || status->time_die < 0
		|| status->time_eat < 0 || status->time_sleep < 0)
		return (1);
	status->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* status->philo_nbr);
	if (ft_malloc_philos(status) == 1)
		return (1);
	return (0);
}
