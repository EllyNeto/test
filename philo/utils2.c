/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:29:47 by eneto             #+#    #+#             */
/*   Updated: 2024/12/04 12:36:06 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wtf(t_philo *philo)
{
	printf("%ld philo %d taken a fork.\n",
		ft_time_diff(philo->status->start_actv), philo->id);
	return ;
}

void	ft_wie(t_philo *philo)
{
	printf("%ld philo %d is eating.\n", ft_time_diff(philo->status->start_actv),
		philo->id);
	return ;
}
