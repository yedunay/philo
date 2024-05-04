/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:02:53 by ydunay            #+#    #+#             */
/*   Updated: 2024/05/04 16:58:27 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define DEBUG_MODE 0

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef enum e_operation_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef enum e_time_code
{
	SEC,
	MSEC,
	USEC,
}						t_time_code;

typedef struct s_table	t_table;

typedef pthread_mutex_t	t_mtx;
typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	int					full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				philo_num;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_limit_meals;
	long				start_sim;
	int					end_sim;
	int					all_threads_ready;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

void					error_exit(const char *error);
void					parse_input(t_table *table, char **av);
void					data_init(t_table *table);
void					*s_malloc(size_t size);
void					s_mutex_handle(t_mtx *mtx, t_opcode opcode);
void					s_thread_handle(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opcode opcode);
void					set_bin(t_mtx *mutex, int *dest, int value);
int						get_bin(t_mtx *mutex, int *value);
long					get_long(t_mtx *mutex, long *value);
void					set_long(t_mtx *mutex, long *dest, long value);
int						sim_finished(t_table *table);
void					wait_all_threads(t_table *table);
long					get_time(t_time_code time_code);
void					precise_usleep(long time, t_table *table);
void					write_status(t_philo_status status, t_philo *philo, int debug);
void    dinner_start(t_table *table);