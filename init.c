/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:06 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/15 10:52:52 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

void	init_philo(t_all *all_data)
{
	int	i;

	i = 0;
	all_data->philosophers = malloc(all_data->global.number_of_philosophers
			* sizeof(t_philo));
	all_data->global.the_start = actual_time();
	all_data->global.have_to_stop = 0;
	all_data->global.all_finish_philo = 0;
	while (i < all_data->global.number_of_philosophers)
	{
		all_data->philosophers[i].id = i;
		all_data->philosophers[i].global_info = &all_data->global;
		all_data->philosophers[i].number_meal_eat = 0;
		all_data->philosophers[i].finish_philo = 0;
		all_data->philosophers[i].left_fork = &all_data->global.mut[i];
		if (all_data->global.number_of_philosophers == 1)
			return ;
		all_data->philosophers[i].right_fork
			= &all_data->global.mut[(i + 1)
			% all_data->global.number_of_philosophers];
		i++;
	}
}

void	init_threads(t_all *all_data)
{
	int	i;

	i = 0;
	all_data->global.threads = (pthread_t *)malloc(
			all_data->global.number_of_philosophers * sizeof(pthread_t));
	while (i < all_data->global.number_of_philosophers)
	{
		pthread_create(&all_data->global.threads[i], NULL,
			philosopher_routine, &all_data->philosophers[i]);
		i++;
	}
}

void	init_mut(t_all *all_data)
{
	int	i;

	i = 0;
	while (i < all_data->global.number_of_philosophers)
	{
		pthread_mutex_init(&(all_data->global.mut[i]), NULL);
		i++;
	}
	pthread_mutex_init(&all_data->global.enable_writing, NULL);
	pthread_mutex_init(&all_data->global.the_dead, NULL);
	pthread_mutex_init(&all_data->global.finish, NULL);
	pthread_mutex_init(&all_data->global.last_meal_enable, NULL);
	pthread_mutex_init(&all_data->global.meal_counter, NULL);
}

void	ft_error(void)
{
	printf("please use valid arguments\nfor example ./philo 3 200 200 200");
	exit(0);
}

void	init_values(int a, char **arg, t_all *all_datas)
{
	if (ft_atoi(arg[1]) == -1 || ft_atoi(arg[1]) == 0)
		ft_error();
	else
		all_datas->global.number_of_philosophers = ft_atoi(arg[1]);
	if (ft_atoi(arg[2]) == -1 || ft_atoi(arg[2]) == 0)
		ft_error();
	else
		all_datas->global.time_to_die = ft_atoi(arg[2]);
	if (ft_atoi(arg[3]) == -1 || ft_atoi(arg[3]) == 0)
		ft_error();
	else
		all_datas->global.time_to_eat = ft_atoi(arg[3]);
	if (ft_atoi(arg[4]) == -1 || ft_atoi(arg[4]) == 0)
		ft_error();
	else
		all_datas->global.time_to_sleep = ft_atoi(arg[4]);
	if (a == 5)
		all_datas->global.max_meal = -1;
	else
	{
		if (ft_atoi(arg[5]) == -1 || ft_atoi(arg[5]) == 0)
			ft_error();
		else
			all_datas->global.max_meal = ft_atoi(arg[5]);
	}
}
