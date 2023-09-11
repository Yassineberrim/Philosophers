/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:08:41 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/11 23:53:27 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int check_n_meals(t_philo *data)
{
    int j = 0;
    while (j < data->general->n_p)
    {
        
        if(data[j].number_meals > data->general->n_e)
            return 0;
        j++;
    }
    return 1;
}
long long gettime_now(void)
{

    struct timeval tv;
    
    if (gettimeofday(&tv, NULL) != 0)
    {
        return -1;
    }
    long long current_time = ((long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000);
    return current_time;
}

void mutex_init(t_general *data)
{
    data->forks = calloc(sizeof(pthread_mutex_t)* data->n_p, 1);
    int i = 0;
    while (i < data->n_p)
    {
        pthread_mutex_init(&data->forks[i],NULL);
        i++;
    }
}

void *routine(void *data)
{
    t_philo *philo = (t_philo*) data;
    
    if (philo->id % 2 == 0)
    {
        printf("%lld %d is thinking\n", gettime_now() - philo->general->start_time, philo->id);
        ft_usleep(philo->general->t_e,philo);
    }
    while (1)
    {
        printf("%lld %d is thinking\n", gettime_now() - philo->general->start_time, philo->id);
        pthread_mutex_lock(&philo->general->forks[philo->right_fork]);
        printf("%lld %d has taken a fork\n", gettime_now() - philo->general->start_time, philo->id);
        pthread_mutex_lock(&philo->general->forks[philo->left_fork]);
        printf("%lld %d has taken a fork\n", gettime_now() - philo->general->start_time, philo->id);
        printf("%lld %d is eating\n", gettime_now() - philo->general->start_time, philo->id);
        pthread_mutex_lock(&philo->general->meals_mutex);
        philo->last_meal = gettime_now();
        philo->number_meals += 1;
        pthread_mutex_unlock(&philo->general->meals_mutex);
        ft_usleep(philo->general->t_e, data);
        pthread_mutex_unlock(&philo->general->forks[philo->right_fork]);
        pthread_mutex_unlock(&philo->general->forks[philo->left_fork]);
        printf("%lld %d is sleeping\n", gettime_now() - philo->general->start_time, philo->id);
        ft_usleep(philo->general->t_s,data);
    }
    return NULL;
}

int main(int ac, char **av)
{
    t_general *general = malloc(sizeof(t_general) * 1);
    general->flag = 0;
        general->n_p = ft_atoi(av[1]);
        general->t_d = ft_atoi(av[2]);
        general->t_e = ft_atoi(av[3]);
        general->t_s = ft_atoi(av[4]);
        if (av[5])
            general->n_e = ft_atoi(av[5]);
        
    t_philo *philos = calloc(sizeof(t_philo) * general->n_p, 1);
    general->start_time = gettime_now();
    mutex_init(general);
    if (ac > 1)
    {
        int i = 0;
        while (i < general->n_p)
        {
            philos[i].id = i + 1;
            philos[i].right_fork = i;
            philos[i].left_fork = (i + general->n_p - 1) % general->n_p;
            philos[i].general = general;
            philos[i].last_meal = gettime_now();
            philos[i].number_meals = 0;
            pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
            i++;
        }
        int j = 0;
        while(1)
        {
            if (av[5] && check_n_meals(philos) == 0)
                return 0;
            //pthread_mutex_lock(philos);
            if(gettime_now() - philos[j].last_meal >= general->t_d)
                {
                    general->flag = 1;
                    printf("%lld %d is died\n", gettime_now() - general->start_time,philos[j].id);
                    return 0;
                }
            j = (j+1) % general->n_p;
            //pthread_mutex_unlock(philos);

        }
        i = 0;
        while (i < general->n_p)
        {
            pthread_join(philos[i].thread, NULL);
            i++;
        }
    }
}
