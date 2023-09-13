/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:20:19 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/13 23:41:48 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->general->mutex_print);
	pthread_mutex_lock(&philo->general->mutex_death);
	if (!philo->general->flag)
		printf("%lld %d %s\n", gettime_now() - philo->general->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->general->mutex_death);
	pthread_mutex_unlock(&philo->general->mutex_print);
}

int	stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->general->mutex_death);
	if (philo->general->flag)
	{
		pthread_mutex_unlock(&philo->general->mutex_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->general->mutex_death);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (stop(philo) == 0)
	{
		print_msg(data, "is thinking");
		pthread_mutex_lock(&philo->general->forks[philo->left_fork]);
		print_msg(data, "has taken a fork");
		pthread_mutex_lock(&philo->general->forks[philo->right_fork]);
		print_msg(data, "has taken a fork");
		philo->last_meal = gettime_now();
		print_msg(data, "is eating");
		pthread_mutex_lock(&philo->general->meals_mutex);
		philo->last_meal = gettime_now();
		pthread_mutex_unlock(&philo->general->meals_mutex);
		ft_usleep(philo->general->t_e, data);
		philo->number_meals += 1;
		pthread_mutex_unlock(&philo->general->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->general->forks[philo->left_fork]);
		print_msg(data, "is sleeping");
		ft_usleep(philo->general->t_s, data);
	}
	return (NULL);
}

int	monitor_philosophers(t_general *general, t_philo *philos)
{
	int	j;

	j = 0;
	while (1)
	{
		if (general->n_e && check_n_meals(philos) == 0)
			return (1);
		if (check_death(philos) == 0)
			return (1);
		j = (j + 1) % general->n_p;
	}
	return (0);
}

void	free_destroy(t_general *general, t_philo *philos, int i)
{
	mutex_destroy(general, i);
	free(general->forks);
	free(general);
	free(philos);
}
