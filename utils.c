#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

long	gettime(int time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (MSEC == time_code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (USEC == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (SECONDS == time_code)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
		error_exit("Wrong input to gettime:"
			"use <MSEC> <USEC> <SECONDS>");
	return (1337);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(USEC);
	while (gettime(USEC) - start < usec)
	{
		if (sim_finished(table))
			break ;
		elapsed = gettime(USEC) - start;
		rem = usec - elapsed;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while (gettime(USEC) - start < usec)
				;
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		s_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	s_mutex_handle(&table->write_mutex, DESTROY);
	s_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	error_exit(const char *error)
{
	printf(RED"🚨 %s 🚨\n"RESET, error);
	exit(EXIT_FAILURE);
}
