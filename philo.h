/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:02:53 by ydunay            #+#    #+#             */
/*   Updated: 2024/04/27 15:12:46 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_table t_table;

typedef struct s_fork
{
    pthread_mutex_t	fork;
    int				fork_id;
}	t_fork;

typedef struct s_philo
{
    int				id;
    long            meals_counter;
    int             full;
    long            last_meal_time;
    t_fork          *left_fork;
    t_fork          *right_fork;
    pthread_t        thread_id;
    t_table         *table;
}	t_philo;

typedef struct s_table
{
    long			philo_num;
    long			time_to_die;
    long			time_to_eat;
    long			time_to_sleep;
    long			num_limit_meals;
    long			start_sim;
    int				end_sim;
    t_fork			*forks;
    t_philo			*philos;
}	t_table;

void    error_exit(const char *error);
