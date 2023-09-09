/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:09:13 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/09 21:40:44 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<limits.h>
#include<stdlib.h>

typedef struct s_general
{
    int t_d;
    int t_s;
    int t_e;
    int n_p;
    int n_e;
    
}               t_general;

typedef struct s_philo
{
    int id;
    pthread_mutex_t  left_fork;
    pthread_mutex_t  right_fork;
    pthread_mutex_t  *mutex;
}                   t_philo;
int	ft_atoi(const char *str);
#endif
