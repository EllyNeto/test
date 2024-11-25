/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:35:01 by eneto             #+#    #+#             */
/*   Updated: 2024/11/22 13:09:53 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_status	*status;

	status = NULL;
	if (argc != 5 && argc != 6)
		return (1);
	status = malloc(sizeof(t_status));
	if (!status)
		return (1);
	if (malloc_struct(status, argv) == 1)
	{
		write(2, "bad malloc\n", 11);
		free(status);
		return (1);
	}
	if (start_routine(status) == 1)
	{
		write(2, "routine error\n", 14);
		free(status);
		return (1);
	}
	return (0);
}
