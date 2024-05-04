#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

void	increase_long(t_mtx *mutex, long *value)
{	
	s_mutex_handle(mutex, LOCK);
	(*value)++;
	s_mutex_handle(mutex, UNLOCK);
}

bool	all_threads_running(t_mtx *mutex, long *threads,
		long philo_num)
{
	bool	ret;

	ret = false;
	s_mutex_handle(mutex, LOCK);
	if (*threads == philo_num)
		ret = true;
	s_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->philo_num % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}	
