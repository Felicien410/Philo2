/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:18 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/15 13:06:07 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

void	philosopher_routine_the_end(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->global_info->enable_writing);
	write_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->global_info->enable_writing);
	ft_usleep(philo->global_info->time_to_sleep);
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->global_info->enable_writing);
	write_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->global_info->enable_writing);
}

void	acquire_forks_and_eat(t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->global_info->enable_writing);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->global_info->enable_writing);
	if (!philo->right_fork)
	{
        pthread_mutex_unlock(philo->left_fork);
		ft_usleep(philo->global_info->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->global_info->enable_writing);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->global_info->enable_writing);
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&philo->global_info->enable_writing);
	write_status("is eating\n", philo);
	pthread_mutex_unlock(&philo->global_info->enable_writing);
	pthread_mutex_lock(&philo->global_info->last_meal_enable);
	philo->last_meal_time = actual_time();
	pthread_mutex_unlock(&philo->global_info->last_meal_enable);
	ft_usleep(philo->global_info->time_to_eat);
}

void	release_forks_and_end_routine(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	if (philo->right_fork)
	{
		pthread_mutex_unlock(philo->right_fork);
	}
	philosopher_routine_the_end(philo);
}

void	philosopher_handle_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->global_info->finish);
	philo->finish_philo = 1;
	philo->global_info->all_finish_philo++;
	if (philo->global_info->all_finish_philo
		== philo->global_info->number_of_philosophers)
	{
		pthread_mutex_unlock(&philo->global_info->finish);
		check_death(philo, 2);
	}
	else
		pthread_mutex_unlock(&philo->global_info->finish);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0 && philo->global_info->number_of_philosophers > 1)
		ft_usleep(philo->global_info->time_to_eat / 10);
	while (check_death(philo, 0) == 0)
	{
		pthread_create(&philo->thread_death_id, NULL, is_dead, philo);
		philosopher_routine_start(philo);
		pthread_detach(philo->thread_death_id);
		philo->number_meal_eat = philo->number_meal_eat + 1;
		pthread_mutex_lock(&philo->global_info->the_dead);
		if (philo->global_info->have_to_stop == 1)
		{
			pthread_mutex_unlock(&philo->global_info->the_dead);
			philosopher_handle_death(philo);
			return (NULL);
		}
		else
			pthread_mutex_unlock(&philo->global_info->the_dead);
		if (philo->number_meal_eat == philo->global_info->max_meal)
		{
			printf("FGHJKL\n");
			philosopher_handle_death(philo);
			return (NULL);
		}

	}
	return (NULL);
}