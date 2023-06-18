/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:08:41 by yberrim           #+#    #+#             */
/*   Updated: 2023/06/18 23:53:39 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int main(int ac, char **av)
{
    t_general philo;
    
    philo.n_p = ft_atoi(av[1]);
    philo.t_d = ft_atoi(av[2]);
    philo.t_e = ft_atoi(av[3]);
    philo.t_s = ft_atoi(av[4]);
    philo.n_e = -1;
    if(av[5])  
        philo.n_e = ft_atoi(av[5]);   
    
}
