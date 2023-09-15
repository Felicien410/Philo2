/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:26 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/15 13:03:22 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

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
}

void	*is_dead(void *arg)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)arg;
	ft_usleep(philo->global_info->time_to_die + 1);
	current_time = actual_time();
	pthread_mutex_lock(&philo->global_info->last_meal_enable);
	pthread_mutex_lock(&philo->global_info->finish);
	if (!check_death(philo, 0) && !philo->finish_philo
		&& (current_time - philo->last_meal_time)
		>= philo->global_info->time_to_die)
	{
		pthread_mutex_unlock(&philo->global_info->last_meal_enable);
		pthread_mutex_unlock(&philo->global_info->finish);
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
		pthread_mutex_unlock(&philo->global_info->last_meal_enable);
		pthread_mutex_unlock(&philo->global_info->finish);
	}
	pthread_exit(NULL);
}


