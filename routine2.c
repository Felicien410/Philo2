/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:38 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/14 08:33:18 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

void	philosopher_routine_start(t_philo *philo)
{
	acquire_forks_and_eat(philo);
	release_forks_and_end_routine(philo);
}
