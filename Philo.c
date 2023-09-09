/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:08:41 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/09 22:05:19 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void *routine(void *data) {
    t_philo *philo = (t_philo*) data;
    printf("Philosopher %d is eating\n", philo->id);
    sleep(2);
    printf("Philosopher %d has finished eating\n", philo->id);
    return NULL;
}

int main(int ac, char **av)
{
    t_general philo;
    pthread_t *threads = malloc(sizeof(pthread_t) * philo.n_p);
    t_philo *philos = malloc(sizeof(t_philo) * philo.n_p);
    
    if (ac > 1)
    {
        philo.n_p = ft_atoi(av[1]);
        philo.t_d = ft_atoi(av[2]);
        philo.t_e = ft_atoi(av[3]);
        philo.t_s = ft_atoi(av[4]);
        philo.n_e = -1;
        if(av[5])  
            philo.n_e = ft_atoi(av[5]);
        int i = 0;
        while (i < philo.n_p)
        {
            philos[i].id = i + 1;
            pthread_create(&threads[i], NULL, &routine, &philos[i]);
            pthread_detach(threads[i]);
            i++;
        }
    }
}
