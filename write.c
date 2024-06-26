/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:38:50 by ydunay            #+#    #+#             */
/*   Updated: 2024/05/05 15:48:11 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <time.h>

static void	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (!sim_finished(philo->table))
	{
		if (status == TAKE_FIRST_FORK)
			printf("%6ld %d has taken the first fork" GREEN " %d.\n" RESET,
				elapsed, philo->id, philo->first_fork->fork_id);
		else if (status == TAKE_SECOND_FORK)
			printf("%6ld %d has taken the second fork" GREEN " %d.\n" RESET,
				elapsed, philo->id, philo->second_fork->fork_id);
		else if (status == EATING)
			printf("%6ld %d is eating." GREEN " %ld.\n" RESET, elapsed,
				philo->id, philo->meals_counter);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping.\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking.\n", elapsed, philo->id);
	}
	else if (status == DIED)
		printf("%-6ld %d died.\n", elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MSEC) - philo->table->start_sim;
	if (philo->full)
		return ;
	s_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else if (!sim_finished(philo->table))
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%-6ld %d has taken a fork.\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%-6ld %d is eating.\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping.\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking.\n", elapsed, philo->id);
	}
	else if (status == DIED)
		printf("%-6ld %d died.\n", elapsed, philo->id);
	s_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
