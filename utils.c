/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:23:18 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/11 15:08:18 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}
int	ft_atoi_helper(const char *str, int i, int sign, long nb)
{
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			write(2, "Error\n", 6);
			// exit(1);
		}
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	nb = (nb * sign);
	if (nb < INT_MIN || nb > INT_MAX)
	{
		write(2, "Error\n", 6);
		// exit(1);
	}
	return (nb);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;
	long	nb;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
	{
		write(2, "Error\n", 6);
		// exit(1);
	}
	return (ft_atoi_helper(str, i, sign, nb));
}

int ft_usleep(unsigned int microseconds)
{
    struct timespec req;
    req.tv_sec = microseconds / 1000000;
    req.tv_nsec = (microseconds % 1000000) * 1000;

    return nanosleep(&req, NULL);
}

// long long	gettime(t_tools *tools)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, 0);
// 	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - (tools->t_0.tv_sec
// 			* 1000 + tools->t_0.tv_usec / 1000));
// }

