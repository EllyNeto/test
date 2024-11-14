/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:35:01 by eneto             #+#    #+#             */
/*   Updated: 2024/11/14 15:08:28 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		start_routine(t_mode *mode)
{
	int i;

	i = 0;
	while(mode->philo_nbr >= i)
	{
		pthread_create(mode->philos[i].thread, NULL, routine, &mode->philos[i]);
		i++;
	}
	i = 0;
	while(mode->philo_nbr >= i)
	{
		ptrhead_join(&mode->philos[i].thread , NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_mode	*mode;

	mode = NULL;
	if (argc != 5 || argc != 6)
		return (1);
	if (malloc_struct(mode, argv) == 1)
	{
		write(2, "bad malloc\n", 11);
		free_all(mode);
		return (1);
	}
	if (start_routine(mode) == 1)
	{
		write(2, "routine error\n", 14);
		free_all(mode);
		return (1);
	}
	return (0);
}
