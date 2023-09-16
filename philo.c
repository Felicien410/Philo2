/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:33 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/16 23:06:38 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

void	write_status(char *str, t_philo *philo)
{
	long int	time;

	time = -1;
	time = actual_time() - philo->g->the_start;
	if (time >= 0 && time <= 2147483647)
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
	pthread_mutex_destroy(&all_data->global.enable_writing);
	pthread_mutex_destroy(&all_data->global.the_dead);
	pthread_mutex_destroy(&all_data->global.finish_unq_philo_mut);

	pthread_mutex_destroy(&all_data->global.check);
	pthread_mutex_destroy(&all_data->global.check_died);
}

void	one_philo(void)
{
	printf("0 1 has taken a fork\n");
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
	if (all_data.global.number_of_philosophers == 1)
		one_philo();
	init_threads(&all_data);
	join_threads(&all_data);
	free_destroy(&all_data);
	free(all_data.global.mut);
	free(all_data.philosophers);
}
