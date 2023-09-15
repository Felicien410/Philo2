/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:33 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/15 15:23:22 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

void	write_status(char *str, t_philo *philo)
{
	long int	time;

	time = -1;
	time = actual_time() - philo->global_info->the_start;
	if (time >= 0 && time <= 2147483647 && !check_death(philo, 0))
	{
		printf("%ld ", time);
		printf("%d %s", philo->id, str);
	}
}

void	free_destroy(t_all *all_data)
{
	int	i;

	i = 0;
	while (i < all_data->global.number_of_philosophers)
	{
		pthread_mutex_destroy(&(all_data->global.mut[i]));
		i++;
	}
	//pthread_mutex_destroy(&all_data->global.enable_writing);
	//pthread_mutex_destroy(&all_data->global.the_dead);
	//pthread_mutex_destroy(&all_data->global.finish);
	//pthread_mutex_destroy(&all_data->global.last_meal_enable);
}

int	main(int argc, char **argv)
{
	t_all	all_data;

	if (argc <= 4 || argc > 6)
		ft_error();
	init_values(argc, argv, &all_data);
	all_data.global.mut = (pthread_mutex_t *)malloc
		(all_data.global.number_of_philosophers * sizeof(pthread_mutex_t));
	init_mut(&all_data);
	init_philo(&all_data);
	init_threads(&all_data);
    join_threads(&all_data);
	free_destroy(&all_data);
/*		int i = 0;
	while ( i < all_data.global.number_of_philosophers)
	{
		free(&(all_data.philosophers[i]));
		i++;
	}*/
	free(all_data.global.mut);
	if (all_data.philosophers)
		free(all_data.philosophers);
}
