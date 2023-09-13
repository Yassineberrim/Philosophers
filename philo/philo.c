/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:08:41 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/13 23:39:36 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_n_meals(t_philo *data)
{
	int	j;

	j = 0;
	while (j < data->general->n_p)
	{
		pthread_mutex_lock(&data->general->meals_mutex);
		if (data[j].number_meals > data->general->n_e)
		{
			pthread_mutex_unlock(&data->general->meals_mutex);
			return (0);
		}
		j++;
		pthread_mutex_unlock(&data->general->meals_mutex);
	}
	return (1);
}

int	check_death(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data->general->n_p)
	{
		pthread_mutex_lock(&data[i].general->meals_mutex);
		if (gettime_now() - data[i].last_meal > data->general->t_d)
		{
			pthread_mutex_unlock(&data[i].general->meals_mutex);
			pthread_mutex_lock(&data[i].general->mutex_death);
			data->general->flag = 1;
			pthread_mutex_unlock(&data[i].general->mutex_death);
			printf("%lld %d is died\n", gettime_now()
				- data[i].general->start_time, data->id);
			return (0);
		}
		pthread_mutex_unlock(&data[i].general->meals_mutex);
		i++;
	}
	return (1);
}

long long	gettime_now(void)
{
	struct timeval	tv;
	long long		current_time;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	current_time = (((long long)(tv.tv_sec)) * 1000) + ((long long)(tv.tv_usec)
			/ 1000);
	return (current_time);
}

void	mutex_init(t_general *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_p);
	i = 0;
	while (i < data->n_p)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->meals_mutex, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
}

int	main(int ac, char **av)
{
	t_general	*general;
	t_philo		*philos;
	int			i;
	int			j;

	if (check_args(ac, av) == 0)
		return (0);
	general = init_argument(av);
	philos = malloc(sizeof(t_philo) * general->n_p);
	mutex_init(general);
	if (ac > 1)
		init_philo(general, philos);
	j = 0;
	while (1)
	{
		if ((av[5] && check_n_meals(philos) == 0) || (check_death(philos) == 0))
			return (0);
		j = (j + 1) % general->n_p;
	}
	i = -1;
	while (++i < general->n_p)
		pthread_join(philos[i].thread, NULL);
	free_destroy(general, philos, i);
	return (0);
}
