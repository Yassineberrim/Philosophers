/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:08:41 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/11 14:00:23 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

long long gettime_now(t_philo *data)
{
    data->
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
    while (1)
    {
        printf("%d is thinking \n",philo->id);
        pthread_mutex_lock(&philo->general->forks[philo->right_fork]);
        pthread_mutex_lock(&philo->general->forks[philo->left_fork]);
        printf("%d has taken a fork\n",philo->id);
        printf("%d has taken a fork\n",philo->id);
        printf("%d is eating\n",philo->id);
        // gettime_now()
        usleep(philo->general->t_e);
        pthread_mutex_unlock(&philo->general->forks[philo->right_fork]);
        pthread_mutex_unlock(&philo->general->forks[philo->left_fork]);
        printf("%d is sleeping\n",philo->id);
        usleep(philo->general->t_s);
        
    }
    return NULL;
}

int main(int ac, char **av)
{
    t_general *general = malloc(sizeof(t_general) * 1);
        general->n_p = ft_atoi(av[1]);
        general->t_d = ft_atoi(av[2]);
        general->t_e = ft_atoi(av[3]);
        general->t_s = ft_atoi(av[4]);
        general->n_e = -1;
    // pthread_t *threads = malloc(sizeof(pthread_t) * philo.n_p);
    t_philo *philos = calloc(sizeof(t_philo) * general->n_p, 1);
    
    mutex_init(general);
    if (ac > 1)
    {
        
        if(av[5])  
            general->n_e = ft_atoi(av[5]);
        int i = 0;
        while (i < general->n_p)
        {
            philos[i].id = i + 1;
            philos[i].right_fork = i;
            philos[i].left_fork = (i + general->n_p - 1) % general->n_p;
            philos[i].general = general;
            pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
            i++;
        }
        i = 0;
        while (i < general->n_p)
        {
            pthread_join(philos[i].thread, NULL);
            i++;
        }
    }
}
