/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:39:06 by ydunay            #+#    #+#             */
/*   Updated: 2024/07/03 14:55:54 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_num;

	philo_num = philo->table->philo_num;
	philo->first_fork = &forks[(philo_position + 1) % philo_num];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_num];
	}
}

static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		if (s_mutex_handle(&philo->philo_mutex, INIT) == -42)
			return (-42);
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
	return (0);
}

int	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = false;
	table->all_threads_ready = false;
	table->threads_running_num = 0;
	table->philos = s_malloc(table->philo_num * sizeof(t_philo));
	if (table->philos == NULL)
		return (-42);
	table->forks = s_malloc(table->philo_num * sizeof(t_fork));
	if (table->forks == NULL)
		return (-42);
	if (s_mutex_handle(&table->write_mutex, INIT) == -42)
		return (-42);
	if (s_mutex_handle(&table->table_mutex, INIT) == -42)
		return (-42);
	while (++i < table->philo_num)
	{
		if (s_mutex_handle(&table->forks[i].fork, INIT) == -42)
			return (-42);
		table->forks[i].fork_id = i;
	}
	if (philo_init(table) == -42)
		return (-42);
	return (0);
}
