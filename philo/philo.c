/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:08:41 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/12 19:24:33 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_n_meals(t_philo *data)
{
    int j = 0;
    while (j < data->general->n_p)
    {
        pthread_mutex_lock(&data->general->meals_mutex);
        if(data[j].number_meals > data->general->n_e)
        {   
            pthread_mutex_unlock(&data->general->meals_mutex);
            return 0;
        }
        j++;
        pthread_mutex_unlock(&data->general->meals_mutex);
    }
    return 1;
}

int check_death(t_philo *data)
{
    int i;

    i = 0;
    while (i < data->general->n_p)
    {
        pthread_mutex_lock(&data[i].general->meals_mutex);
        if (gettime_now() - data[i].last_meal > data->general->t_d )
        {
            pthread_mutex_unlock(&data[i].general->meals_mutex);
            pthread_mutex_lock(&data[i].general->mutex_death);
            data->general->flag = 1;
            pthread_mutex_unlock(&data[i].general->mutex_death);
            printf("%lld %d is died\n", gettime_now() - data[i].general->start_time,data->id);
            return 0;
        }
        pthread_mutex_unlock(&data[i].general->meals_mutex);
        i++;
    }

    return 1;
}

long long gettime_now(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
        return -1;
    long long current_time = ((long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000);
    return current_time;
}

void mutex_init(t_general *data)
{
    data->forks = malloc(sizeof(pthread_mutex_t)* data->n_p);
    int i = 0;
    while (i < data->n_p)
    {
        pthread_mutex_init(&data->forks[i],NULL);
        i++;
    }
    pthread_mutex_init(&data->meals_mutex, NULL);
    pthread_mutex_init(&data->mutex_death, NULL);
    pthread_mutex_init(&data->mutex_print, NULL);
}

void    print_msg(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->general->mutex_print);
    pthread_mutex_lock(&philo->general->mutex_death);
    if (!philo->general->flag)
        printf("%lld %d %s\n", gettime_now() - philo->general->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->general->mutex_death);
    pthread_mutex_unlock(&philo->general->mutex_print);
}

int stop(t_philo *philo)
{
    pthread_mutex_lock(&philo->general->mutex_death);
    if (philo->general->flag)
    {
        pthread_mutex_unlock(&philo->general->mutex_death);
        return 1;
    }
    pthread_mutex_unlock(&philo->general->mutex_death);
    return 0;
}

void *routine(void *data)
{
    t_philo *philo = (t_philo*) data;
    
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
        
    t_philo *philos = malloc(sizeof(t_philo) * general->n_p);
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
            usleep(100);
            i++;
        }
        int j = 0;
        while(1)
        {
            if (av[5] && check_n_meals(philos) == 0)
                return 0;
            if (check_death(philos) == 0)
                return 0;
            j = (j+1) % general->n_p;
        }
        i = 0;
        while (i < general->n_p)
        {
            pthread_join(philos[i].thread, NULL);
            i++;
        }
    }
}
