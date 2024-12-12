/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:35:01 by eneto             #+#    #+#             */
/*   Updated: 2024/12/11 08:36:42 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!((argv[i][j] >= '0' && argv[i][j] <= '9') || argv[i][j] == ' '
					|| argv[i][j] == '\t' || argv[i][j] == '-'
					|| argv[i][j] == '+'))
				return (1);
			j++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_status	*status;

	status = NULL;
	if (argc != 5 && argc != 6)
		return (1);
	if (ft_check_args(argc, argv))
		return (1);
	status = malloc(sizeof(t_status));
	if (status == NULL)
		return (1);
	if (ft_malloc_struct(status, argv) == 1)
	{
		write(2, "Parametros errados!\n", 19);
		free(status);
		return (1);
	}
	if (ft_start_routine(status) == 1)
	{
		write(2, "routine error\n", 14);
		ft_free_all(status);
		return (1);
	}
	ft_free_all(status);
	return (0);
}
