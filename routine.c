/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:18 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/16 22:57:01 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

void	acquire_forks_and_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->g->check_died);
	if (philo->g->philo_died == 0 && philo->g->all_finish_philo == 0)
	{
		write_status("has taken a fork\n", philo);
		write_status("has taken a fork\n", philo);
		write_status("is eating\n", philo);
		pthread_mutex_unlock(&philo->g->check_died);
	}
	else
		pthread_mutex_unlock(&philo->g->check_died);
}

void	print_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->g->check);
	if (philo->g->all_finish_philo == 0)
	{
		pthread_mutex_lock(&philo->g->check_died);
		if (philo->g->philo_died)
		{
			pthread_mutex_unlock(&philo->g->check);
			pthread_mutex_unlock(&philo->g->check_died);
			return ;
		}
		if (!philo->g->philo_died)
		{
			write_status("is sleeping\n", philo);
			pthread_mutex_unlock(&philo->g->check_died);
			pthread_mutex_unlock(&philo->g->check);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->g->check);
	return ;
}

void	print_thinking_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->g->check);
	if (philo->g->all_finish_philo == 0)
	{
		pthread_mutex_lock(&philo->g->check_died);
		if (philo->g->philo_died)
		{
			pthread_mutex_unlock(&philo->g->check);
			pthread_mutex_unlock(&philo->g->check_died);
			return ;
		}
		if (!philo->g->philo_died)
		{
			write_status("is thinking\n", philo);
			pthread_mutex_unlock(&philo->g->check_died);
			pthread_mutex_unlock(&philo->g->check);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->g->check);
	return ;
}

void	philosopher_routine_start(t_philo *philo)
{
	philo_eat(philo);
	print_sleep_routine(philo);
	print_thinking_routine(philo);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0 && philo->g->number_of_philosophers > 1)
		ft_usleep(philo->g->time_to_eat / 10);
	while (1)
	{
		pthread_mutex_lock(&philo->g->check_died);
		if (philo->g->number_of_philosophers > 1 && philo->g->philo_died == 0
			&& philo->g->all_finish_philo == 0 && !philo->done_eating)
		{
			pthread_mutex_unlock(&philo->g->check_died);
			philosopher_routine_start(philo);
			ft_usleep(400);
		}
		else
		{
			pthread_mutex_unlock(&philo->g->check_died);
			break ;
		}
	}
	return (NULL);
}
