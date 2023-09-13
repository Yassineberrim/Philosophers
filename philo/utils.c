/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:23:18 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/13 23:42:01 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (-1);
	}
	return (ft_atoi_helper(str, i, sign, nb));
}

void	ft_usleep(int time, t_philo *data)
{
	struct timeval	sleep;
	struct timeval	sleep2;

	gettimeofday(&sleep, 0);
	while (1)
	{
		pthread_mutex_lock(&data->general->meals_mutex);
		if (data->last_meal == 1)
			break ;
		pthread_mutex_unlock(&data->general->meals_mutex);
		usleep(100);
		gettimeofday(&sleep2, 0);
		if (((sleep2.tv_sec * 1000 + sleep2.tv_usec / 1000) - (sleep.tv_sec
					* 1000 + sleep.tv_usec / 1000)) >= time)
			return ;
	}
	pthread_mutex_unlock(&data->general->meals_mutex);
}

void	mutex_destroy(t_general *general, int i)
{
	while (i < general->n_p)
	{
		pthread_mutex_destroy(&general->forks[i]);
		i++;
	}
}

void	init_philo(t_general *general, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < general->n_p)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = i;
		philos[i].left_fork = (i + general->n_p - 1) % general->n_p;
		philos[i].general = general;
		philos[i].last_meal = gettime_now();
		philos[i].number_meals = 0;
		pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
		usleep(50);
		i++;
	}
}

t_general	*init_argument(char **av)
{
	t_general	*general;

	general = malloc(sizeof(t_general) * 1);
	general->flag = 0;
	general->n_p = ft_atoi(av[1]);
	general->t_d = ft_atoi(av[2]);
	general->t_e = ft_atoi(av[3]);
	general->t_s = ft_atoi(av[4]);
	if (av[5])
		general->n_e = ft_atoi(av[5]);
	general->start_time = gettime_now();
	return (general);
}
