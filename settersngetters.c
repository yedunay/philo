#include "philo.h"

void	set_bin(t_mtx *mutex, int *dest, int value)
{
	s_mutex_handle(mutex, LOCK);
	*dest = value;
	s_mutex_handle(mutex, UNLOCK);
}

int	get_bin(t_mtx *mutex, int *value)
{
	int retval;

	s_mutex_handle(mutex, LOCK);
	retval = *value;
	s_mutex_handle(mutex, UNLOCK);
	return (retval);
}

long    get_long(t_mtx *mutex, long *value)
{
    long retval;

	s_mutex_handle(mutex, LOCK);
	retval = *value;
	s_mutex_handle(mutex, UNLOCK);
	return (retval);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	s_mutex_handle(mutex, LOCK);
	*dest = value;
	s_mutex_handle(mutex, UNLOCK);
}

int sim_finished(t_table *table)
{
    return (get_bin(&table->table_mutex, &table->end_sim));
}