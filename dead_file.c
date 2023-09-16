/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:26 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/16 22:08:01 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

int	handle_single_philosopher(t_philo *philo)
{
	ft_usleep(philo->g->time_to_die);
	pthread_mutex_lock(&philo->g->enable_writing);
	write_status("died\n", philo);
	pthread_mutex_unlock(&philo->g->enable_writing);
	return (1);
}

int	check_death_time(t_philo *philo, long int actual)
{
	if (diffe_time(actual, philo->last_meal_time) > philo->g->time_to_die)
	{
		pthread_mutex_lock(&philo->g->check_died);
		philo->g->philo_died = 1;
		pthread_mutex_unlock(&philo->g->check_died);
		if (philo->g->philo_died == 1)
		{
			pthread_mutex_lock(&philo->g->enable_writing);
			write_status("died\n", philo);
			pthread_mutex_unlock(&philo->g->enable_writing);
		}
		pthread_mutex_unlock(&philo->g->check);
		return (1);
	}
	return (0);
}

int	print_dead(t_philo *philo)
{
	long int	actual;

	actual = actual_time();
	if (philo->g->number_of_philosophers == 1)
		return (handle_single_philosopher(philo));
	return (check_death_time(philo, actual));
}

void	check_satisfaction_and_finish(t_all *all, int i)
{
	pthread_mutex_lock(&all->global.check_died);
	if (all->philosophers[i].philo_ate == all->global.max_meal
		&& !all->philosophers[i].done_eating)
	{
		all->global.almost_satisfied++;
		all->philosophers[i].done_eating++;
	}
	if (all->global.almost_satisfied == all->global.number_of_philosophers)
		all->global.all_finish_philo = 1;
	pthread_mutex_unlock(&all->global.check_died);
}

void	dead_check(void *arg)
{
	t_all	*all;
	int		i;

	all = (t_all *)arg;
	while (all->global.all_finish_philo == 0 && all->global.philo_died == 0)
	{
		i = -1;
		while (++i < all->global.number_of_philosophers)
		{
			pthread_mutex_lock(&all->global.check);
			if (print_dead(&all->philosophers[i]) == 1)
				return ;
			check_satisfaction_and_finish(all, i);
			pthread_mutex_unlock(&all->global.check);
		}
	}
}
