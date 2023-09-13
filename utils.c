#include"Includes/philo.h"

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
	int	i;
	int	neg;
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
			return(-1);
		result = result * 10 + str[i] - '0';
		i ++;
	}
	return (result * neg);
}