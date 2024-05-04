#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks,
		int philo_position)
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

static void	philo_init(t_table *table)
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
		s_mutex_handle(&philo->philo_mutex, INIT);
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int		i;

	i = -1;
	table->end_sim = false;
	table->all_threads_ready = false;
	table->threads_running_num = 0;
	table->philos = s_malloc(table->philo_num * sizeof(t_philo));
	table->forks = s_malloc(table->philo_num * sizeof(t_fork));
	s_mutex_handle(&table->write_mutex, INIT);
	s_mutex_handle(&table->table_mutex, INIT);
	while (++i < table->philo_num)
	{
		s_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
