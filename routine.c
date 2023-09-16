/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:18 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/16 18:49:26 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

void	acquire_forks_and_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->global_info->check_died);
	if (philo->global_info->philo_died == 0 && philo->global_info->all_finish_philo == 0)
	{
		//pthread_mutex_lock(&philo->global_info->enable_writing);
		write_status("has taken a fork\n", philo);
		//pthread_mutex_unlock(&philo->global_info->enable_writing);
		
		//pthread_mutex_lock(&philo->global_info->enable_writing);
		write_status("has taken a fork\n", philo);
		//pthread_mutex_unlock(&philo->global_info->enable_writing);
		
		//pthread_mutex_lock(&philo->global_info->enable_writing);
		write_status("is eating\n", philo);
		//pthread_mutex_unlock(&philo->global_info->enable_writing);
		
		pthread_mutex_unlock(&philo->global_info->check_died);
	}
	else
	{
		pthread_mutex_unlock(&philo->global_info->check_died);	
	}
}


void	print_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->global_info->check);
	if (philo->global_info->all_finish_philo == 0)
	{
		pthread_mutex_lock(&philo->global_info->check_died);
		if(philo->global_info->philo_died)
		{
			pthread_mutex_unlock(&philo->global_info->check);
			pthread_mutex_unlock(&philo->global_info->check_died);
			return ;
		}
		if(!philo->global_info->philo_died)
		{
			//pthread_mutex_lock(&philo->global_info->enable_writing);
			write_status("is sleeping\n", philo);
			//pthread_mutex_unlock(&philo->global_info->enable_writing);
			pthread_mutex_unlock(&philo->global_info->check_died);
			pthread_mutex_unlock(&philo->global_info->check);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->global_info->check);
	return ;
}

void	print_thinking_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->global_info->check);
	if (philo->global_info->all_finish_philo == 0)
	{
		pthread_mutex_lock(&philo->global_info->check_died);
		if(philo->global_info->philo_died)
		{
			pthread_mutex_unlock(&philo->global_info->check);
			pthread_mutex_unlock(&philo->global_info->check_died);
			return ;
		}
		if(!philo->global_info->philo_died)
		{
			pthread_mutex_lock(&philo->global_info->enable_writing);
			write_status("is thinking\n", philo);
			pthread_mutex_unlock(&philo->global_info->enable_writing);
			pthread_mutex_unlock(&philo->global_info->check_died);
			pthread_mutex_unlock(&philo->global_info->check);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->global_info->check);
	return ;
}

void	eat_routine(t_philo *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	gettimeofday(&current_time, NULL);
	
	acquire_forks_and_eat(philo);
	
	pthread_mutex_lock(&philo->global_info->check);
	philo->philo_ate += 1;
	philo->last_meal_time = actual_time();
	pthread_mutex_unlock(&philo->global_info->check);

	ft_usleep(philo->global_info->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_routine(t_philo *philo)
{
	print_sleep_routine(philo);
	ft_usleep(philo->global_info->time_to_sleep);
}

void	thinking_routine(t_philo *philo)
{
	print_thinking_routine(philo);
}

void	philosopher_routine_start(t_philo *philo)
{
	eat_routine(philo);
	print_sleep_routine(philo);
	print_thinking_routine(philo);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0 && philo->global_info->number_of_philosophers > 1)
		ft_usleep(philo->global_info->time_to_eat / 10);
	while (1)
	{
		pthread_mutex_lock(&philo->global_info->check_died);
		if (philo->global_info->number_of_philosophers > 1 && philo->global_info->philo_died == 0
			&& philo->global_info->all_finish_philo == 0 && !philo->done_eating)
		{
			pthread_mutex_unlock(&philo->global_info->check_died);
			philosopher_routine_start(philo);
			ft_usleep(500);
		}
		else
		{
			pthread_mutex_unlock(&philo->global_info->check_died);
			break;
		}
	}
	return (NULL);
}

/*
void	*philo_routine(void *philo)
{
	t_input_args	*input_args;
	t_philo			*p;

	p = (t_philo *)philo;
	input_args = p->args;
	while (1)
	{
		pthread_mutex_lock(&input_args->check_died);
		if (input_args->nb_philos > 1 && input_args->phi_died == 0
			&& input_args->all_phi_ate == 0 && !p->done_eating)
		{
			pthread_mutex_unlock(&input_args->check_died);
			eat_routine(p);
			sleep_routine(input_args, p->philo_id);
			thinking_routine(p, input_args);
			usleep(500);
		}
		else
		{
			pthread_mutex_unlock(&input_args->check_died);
			break ;
		}
	}
	return (NULL);
}
*/

/*
void	philosopher_handle_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->global_info->finish_unq_philo_mut);
	philo->finish_unq_philo = 1;
	philo->global_info->all_finish_philo++;
	if (philo->global_info->all_finish_philo
		== philo->global_info->number_of_philosophers)
	{
		pthread_mutex_unlock(&philo->global_info->finish_unq_philo_mut);
		check_death(philo, 2);
	}
	else
		pthread_mutex_unlock(&philo->global_info->finish_unq_philo_mut);
}*/

/*
void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0 && philo->global_info->number_of_philosophers > 1)
		ft_usleep(philo->global_info->time_to_eat / 10);
		
	while (1)
	{
		pthread_create(&philo->thread_death_id, NULL, is_dead, philo);
		philosopher_routine_start(philo);
		
		pthread_detach(philo->thread_death_id);
		printf("je viens d en detacher un\n");
		
		pthread_mutex_lock(&philo->global_info->number_eat_meal);
		philo->number_meal_eat = philo->number_meal_eat + 1;
		pthread_mutex_unlock(&philo->global_info->number_eat_meal);

		if (philo->global_info->have_to_stop == 1)
		{
			philosopher_handle_death(philo);
			return (NULL);
		}
	
		if (philo->number_meal_eat == philo->global_info->max_meal)
		{
			printf("GHJK");
			philosopher_handle_death(philo);
			return (NULL);
		}
	}
	return (NULL);
}*/