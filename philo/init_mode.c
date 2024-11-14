/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:24:30 by eneto             #+#    #+#             */
/*   Updated: 2024/11/14 13:22:48 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     malloc_philos(t_mode *mode)
{
    int i;

    i = 0;
    mode->philos = malloc(sizeof(t_philo) * mode->philo_nbr);
    if (mode->philos == NULL)
        return (1);
    while(mode->philos > i)
    {
        mode->philos[i].id = i + 1;
        mode->philos[i].meals_counter = 0;
        mode->philos[i].last_meal_time = mode->start_actv;
        mode->philos[i].full = 0;
        i++;   
    }
    return (0);
}

int	malloc_struct(t_mode *mode, char **argv)
{
	mode = malloc(sizeof(t_mode));
	if (!mode)
		return (1);
	mode->philo_nbr = ft_atol(argv[1]);
	mode->time_die = ft_atol(argv[2]);
	mode->time_eat = ft_atol(argv[3]);
	mode->time_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		mode->nbr_limit_meals = ft_atol(argv[5]);
	else
		mode->nbr_limit_meals = ft_atol(argv[5]);
	mode->start_actv = ft_get_time_in_milis();
	mode->end_actv = 0;
	mode->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* mode->philo_nbr);
	if (malloc_philos(mode) == 1)
		return (1);
	if ((argv[5] != NULL && mode->nbr_limit_meals < 0) || mode->philo_nbr <= 0
		|| mode->time_die < 0 || mode->time_eat < 0 || mode->time_sleep < 0)
		return (1);
	return (0);
}
