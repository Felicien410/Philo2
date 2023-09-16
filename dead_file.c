/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:26 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/16 18:48:05 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"
/*
int	check_death(t_philo *philo, int i)
{
	int	should_stop;

	should_stop = 0;
	pthread_mutex_lock(&philo->global_info->the_dead);
	if (i != 0)
		philo->global_info->have_to_stop = i;
	if (philo->global_info->have_to_stop == 1)
		should_stop = 1;
	pthread_mutex_unlock(&philo->global_info->the_dead);
	return (should_stop);
}*/

long	diffe_time(int actual_time, int previous_time)
{
	return (actual_time - previous_time);
}

int	print_dead(t_philo *philo)
{
	long int actual;
	//long	time;

	actual = actual_time();
	//time = diffe_time(actual, philo->global_info->time);
	if (diffe_time(actual, philo->last_meal_time) > philo->global_info->time_to_die)
	{
		pthread_mutex_lock(&philo->global_info->check_died);
		philo->global_info->philo_died = 1;
		pthread_mutex_unlock(&philo->global_info->check_died);
		if(philo->global_info->philo_died == 1)
		{
			pthread_mutex_lock(&philo->global_info->enable_writing);
			write_status("died\n", philo);
			pthread_mutex_unlock(&philo->global_info->enable_writing);
		}
		pthread_mutex_unlock(&philo->global_info->check);
		return (1);
	}
	return (0);
}

void	dead_check(void *arg)
{
	t_all	*all;
	//long	current_time;
	int i;
	
	all = (t_all *)arg;
	while (all->global.all_finish_philo == 0
		&& all->global.philo_died == 0)
	{
		i = -1;
		while(++i < all->global.number_of_philosophers)
		{
			pthread_mutex_lock(&all->global.check);
			if(print_dead(&all->philosophers[i]) == 1)
				return ;
			pthread_mutex_lock(&all->global.check_died);
			if (all->philosophers[i].philo_ate == all->global.max_meal
				&& !all->philosophers[i].done_eating)
			{
				all->global.almost_satisfied++;
				all->philosophers[i].done_eating++;
			}
			if(all->global.almost_satisfied == all->global.number_of_philosophers)
			{
				all->global.all_finish_philo = 1;
			}
			pthread_mutex_unlock(&all->global.check_died);
			pthread_mutex_unlock(&all->global.check);
		}
	}

}
/*
void	*is_dead(void *arg)
{
	t_philo	*philo;
	long	current_time;
	
	philo = (t_philo *)arg;
	//pthread_mutex_lock(&philo->global_info->time_to_die_mut); //ici si tu les met ca enlenve pour 5 arg mais ca en remet un a 4
	ft_usleep(philo->global_info->time_to_die + 1);
	//pthread_mutex_unlock(&philo->global_info->time_to_die_mut);
	
	current_time = actual_time();
	pthread_mutex_lock(&philo->global_info->time_to_die_mut); //ici si tu les met ca enlenve pour 5 arg mais ca en remet un a 4
	pthread_mutex_lock(&philo->global_info->check);
	pthread_mutex_lock(&philo->global_info->finish_unq_philo_mut);
	if (!check_death(philo, 0) && !philo->finish_unq_philo
		&& (current_time - philo->last_meal_time)
		>= philo->global_info->time_to_die)
	{
		pthread_mutex_unlock(&philo->global_info->check);
		pthread_mutex_unlock(&philo->global_info->time_to_die_mut);
		pthread_mutex_unlock(&philo->global_info->finish_unq_philo_mut);
		
		pthread_mutex_lock(&philo->global_info->enable_writing);
		write_status("died\n", philo);
		pthread_mutex_unlock(&philo->global_info->enable_writing);
		//pthread_detach(philo->thread_death_id);
		//pthread_mutex_lock(&philo->global_info->the_dead);
		//philo->global_info->have_to_stop = 1;
		//pthread_mutex_unlock(&philo->global_info->the_dead);
		check_death(philo, 1);
	}
	else
	{
		pthread_mutex_unlock(&philo->global_info->check);
		pthread_mutex_unlock(&philo->global_info->finish_unq_philo_mut);
	}
	pthread_exit(NULL);
}*/