/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:38 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/16 22:30:48 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

void	philo_eat(t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	gettimeofday(&current_time, NULL);
	acquire_forks_and_eat(philo);
	pthread_mutex_lock(&philo->g->check);
	philo->philo_ate += 1;
	philo->last_meal_time = actual_time();
	pthread_mutex_unlock(&philo->g->check);
	ft_usleep(philo->g->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_sleep_routine(philo);
	ft_usleep(philo->g->time_to_sleep);
}
