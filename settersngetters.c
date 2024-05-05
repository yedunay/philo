/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settersngetters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:38:57 by ydunay            #+#    #+#             */
/*   Updated: 2024/05/05 15:38:58 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	s_mutex_handle(mutex, LOCK);
	*dest = value;
	s_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	s_mutex_handle(mutex, LOCK);
	ret = *value;
	s_mutex_handle(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	s_mutex_handle(mutex, LOCK);
	ret = *value;
	s_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	s_mutex_handle(mutex, LOCK);
	*dest = value;
	s_mutex_handle(mutex, UNLOCK);
}

bool	sim_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_sim));
}
