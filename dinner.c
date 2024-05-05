/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:39:05 by ydunay            #+#    #+#             */
/*   Updated: 2024/05/05 15:39:06 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_num % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MSEC));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_num);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!sim_finished(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	s_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	s_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MSEC));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->num_limit_meals > 0
		&& philo->meals_counter == philo->table->num_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	s_mutex_handle(&philo->first_fork->fork, UNLOCK);
	s_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

static void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MSEC));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_num);
	de_synchronize_philos(philo);
	while (!sim_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->num_limit_meals == 0)
		return ;
	else if (table->philo_num == 1)
		s_thread_handle(&table->philos[0].thread_id, lone_philo,
			&table->philos[0], CREATE);
	else
		while (++i < table->philo_num)
			s_thread_handle(&table->philos[i].thread_id, dinner_sim,
				&table->philos[i], CREATE);
	s_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_sim = gettime(MSEC);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_num)
		s_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_sim, true);
	s_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
