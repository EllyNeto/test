/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:35:01 by eneto             #+#    #+#             */
/*   Updated: 2024/11/19 15:51:47 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_mode	*mode;

	mode = NULL;
	if (argc != 5 && argc != 6)
		return (1);
	mode = malloc(sizeof(t_mode));
	if (!mode)
		return (1);
	if (malloc_struct(mode, argv) == 1)
	{
		write(2, "bad malloc\n", 11);
		free(mode);
		return (1);
	}
	if (start_routine(mode) == 1)
	{
		write(2, "routine error\n", 14);
		free(mode);
		return (1);
	}
	return (0);
}
