/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:32:43 by eneto             #+#    #+#             */
/*   Updated: 2024/12/01 14:54:41 by eneto            ###   ########.fr       */
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
typedef struct s_status	t_status;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		meal_lock;
	long				meals_counter;
	long				last_meal_time;
	int					full;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread;
	t_status			*status;
}						t_philo;

typedef struct s_status
{
	int					philo_nbr;
	long				time_die;
	long				time_eat;
	int					time_sleep;
	long				nbr_limit_meals;
	long				start_actv;
	int					end_actv;
	pthread_mutex_t		end_actv_lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_status;
// functioms aux
void					verify(t_philo *vrf);
void					ft_free_all(t_status *philo);
void					limit_meals(t_status *meals_l);
long					ft_time_diff(long time);
long					ft_get_time_in_milis(void);
long					ft_atol(char *str);

// philo alive
int						ft_start_routine(t_status *status);
void					*ft_routine(void *m);
int						ft_malloc_philos(t_status *status);
int						ft_malloc_struct(t_status *status, char **argv);

// status
void					t_eat(t_philo *philo);
void					v_status(t_status *status);
void					t_think(t_philo *philo);
void					t_sleep(t_philo *philo);

#endif
