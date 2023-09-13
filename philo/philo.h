/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:09:13 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/13 23:36:32 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_general
{
	int				t_d;
	int				t_s;
	int				t_e;
	int				n_p;
	int				n_e;
	time_t			start_time;
	int				flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_print;
}					t_general;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				number_meals;
	int				left_fork;
	int				right_fork;
	t_general		*general;
	pthread_t		thread;
}					t_philo;
void				ft_usleep(int time, t_philo *ph);
long long			gettime_now(void);
int					ft_atoi(const char *str);
int					check_n_meals(t_philo *data);
void				*routine(void *data);
int					ft_atoi(const char *str);
void				ft_usleep(int time, t_philo *ph);
int					ft_isdigit(int c);
int					ft_atoi_helper(const char *str, int i, int sign, long nb);
int					check_args_part2(int ac, char **av);
void				mutex_destroy(t_general *general, int i);
void				init_philo(t_general *general, t_philo *philos);
int					monitor_philosophers(t_general *general, t_philo *philos);
int					check_args(int ac, char **av);
t_general			*init_argument(char **av);
void				mutex_init(t_general *data);
int					check(t_philo *philos);
int					check_death(t_philo *data);
void				free_destroy(t_general *general, t_philo *philos, int i);
#endif
