/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 08:37:08 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/16 17:04:59 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stddef.h>
# include <unistd.h>

typedef struct s_global
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meal;
	long			the_start;
	int				have_to_stop;
	pthread_t		*threads;
	pthread_t		*death_check_threads;
	
	pthread_mutex_t	enable_writing;
	pthread_mutex_t	the_dead;
	pthread_mutex_t	*mut;
	pthread_mutex_t	finish_unq_philo_mut;
	
	pthread_mutex_t	time_to_die_mut;
	pthread_mutex_t	number_eat_meal;
	pthread_mutex_t	check;
	pthread_mutex_t	check_died;
	int				philo_died;
	int			almost_satisfied;
	long			all_finish_philo;
	long			time;
}					t_global;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_global		*global_info;
	long			number_meal_eat;
	int				finish_unq_philo;
	int				philo_ate;
	int				done_eating;
}					t_philo;

typedef struct s_all
{
	t_philo		*philosophers;
	t_global	global;
}	t_all;

void	write_status(char *str, t_philo *philo);
long		actual_time(void);
void		ft_usleep(long time);
void		write_status(char *str, t_philo *philo);
void		*philosopher_routine(void *arg);
void		philosopher_routine_start(t_philo *philo);
void		acquire_forks_and_eat(t_philo *philo);
void		release_forks_and_end_routine(t_philo *philo);
void		init_threads(t_all *all_data);
void		init_philo(t_all *all_data);
void		init_mut(t_all *all_data);
void		ft_error(void);
void		init_values(int a, char **arg, t_all *all_datas);
void		ft_putstr_fd(char *s, int fd);
long		ft_atoi(const char *str);
void join_threads(t_all *all_data);
void	dead_check(void *arg);
int	print_dead(t_philo *philo);

#endif
