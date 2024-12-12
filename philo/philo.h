/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eneto <eneto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:32:43 by eneto             #+#    #+#             */
/*   Updated: 2024/12/12 08:12:35 by eneto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_status	t_status;

typedef struct s_philo
{
	int					id;
	int					full;
	long				meals_counter;
	long				last_meal_time;
	pthread_t			thread;
	t_status			*status;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
}						t_philo;

typedef struct s_status
{
	long				time_die;
	long				time_eat;
	int					end_actv;
	int					philo_nbr;
	long				time_sleep;
	long				start_actv;
	long				nbr_limit_meals;
	pthread_mutex_t		lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	pthread_mutex_t		actv_lock;
	pthread_mutex_t		end_actv_lock;
}						t_status;
// functioms aux
long					ft_atol(char *str);
void					verify(t_philo *vrf);
void					ft_wtf(t_philo *philo);
void					ft_wie(t_philo *philo);
long					ft_time_diff(long time);
long					ft_get_time_in_milis(void);
void					ft_ini_f(t_status *status);
void					ft_free_all(t_status *philo);
void					limit_meals(t_status *meals_l);
void					ft_sleep(long time_in_ms, t_philo *philo);

// philo alive
void					*ft_routine(void *m);
int						ft_start_routine(t_status *status);
int						ft_malloc_philos(t_status *status);
int						ft_malloc_struct(t_status *status, char **argv);

// status
void					t_eat(t_philo *philo);
void					t_think(t_philo *philo);
void					t_sleep(t_philo *philo);
void					v_status(t_status *status);

#endif
