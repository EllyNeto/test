/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:32:43 by eneto             #+#    #+#             */
/*   Updated: 2024/11/14 15:16:58 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //gettimeofday
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	long				last_meal_time;
	int					full;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	t_mode				*mode;
}						t_philo;

typedef struct s_mode
{
	int					philo_nbr;
	long				time_die;
	long				time_eat;
	int					time_sleep;
	long				nbr_limit_meals;
	long				start_actv;
	int					end_actv;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_mode;
// functioms aux
long					ft_time_diff(long time);
long					ft_get_time_in_milis(void);
long					ft_atol(char *str);

//
int						start_routine(t_mode *mode);
int						routine(void);
int						malloc_philos(t_mode *mode);
int						malloc_struct(t_mode *mode, char **argv);

#endif
