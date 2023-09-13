/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:21:22 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/13 22:18:51 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
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
			return (-1);
		}
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	nb = (nb * sign);
	if (nb < INT_MIN || nb > INT_MAX)
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	return (nb);
}

int	check_args_part2(int ac, char **av)
{
	if (ft_atoi(av[1]) > 200)
	{
		printf("Error: wrong number of philosophers\n");
		return (0);
	}
	else if (ft_atoi(av[4]) < 60)
	{
		printf("Error: wrong time to sleep\n");
		return (0);
	}
	else if (ac == 6 && ft_atoi(av[5]) < 0)
	{
		printf("Error: wrong max eat number\n");
		return (0);
	}
	else if (ft_atoi(av[1]) < 0 || ft_atoi(av[2]) < 0 || ft_atoi(av[3]) < 0
		|| ft_atoi(av[4]) < 0)
	{
		printf("Error: wrong argument\n");
		return (0);
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	else if (ft_atoi(av[1]) < 1)
	{
		printf("Error: wrong number of philosophers\n");
		return (0);
	}
	else if (ft_atoi(av[2]) < 60)
	{
		printf("Error: wrong time to die\n");
		return (0);
	}
	else if (ft_atoi(av[3]) < 60)
	{
		printf("Error: wrong time to eat\n");
		return (0);
	}
	if (!check_args_part2(ac, av))
		return (0);
	return (1);
}
