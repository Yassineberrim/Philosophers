/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:09:13 by yberrim           #+#    #+#             */
/*   Updated: 2023/06/18 22:29:21 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<limits.h>

typedef struct s_general
{
    int t_d;
    int t_s;
    int t_e;
    int n_p;
    int n_e;
    
}t_general;

// typedef struct s_philo
// {
//     int ;
    
    
// }t_philo;
int	ft_atoi(const char *str);
#endif