/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:31:51 by fcatteau          #+#    #+#             */
/*   Updated: 2023/09/14 11:13:05 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write (fd, &s[i], 1);
			i++;
		}
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	result;

	i = 0;
	neg = 1;
	result = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] != '\0' && str[i] == '-')
	{
		return (-1);
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit (str[i]) == 0)
			return (-1);
		result = result * 10 + str[i] - '0';
		i ++;
	}
	return (result * neg);
}

void join_threads(t_all *all_data)
{
	int i;
	
	i = 0;
	while (i < all_data->global.number_of_philosophers)
	{
		pthread_join(all_data->global.threads[i], NULL);
		i++;
	}
	free(all_data->global.threads);
}