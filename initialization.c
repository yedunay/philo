#include "philo.h"

static void assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
    int philo_num;

    philo_num = philo->table->philo_num;
    philo->first_fork = &forks[(philo_pos + 1) % philo_num];
    philo->second_fork = &forks[philo_pos];
    if(philo->id % 2 == 1)
    {
        philo->first_fork = &forks[philo_pos];
        philo->second_fork = &forks[(philo_pos + 1) % philo_num];
    }
}

static void philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = -1;
    while(++i < table->philo_num)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = 0;
        philo->meals_counter = 0;
        philo->table = table;
        assign_forks(philo, table->forks, i);
    }
}

void    data_init(t_table *table)
{
    int i;

    i = -1;
    table->end_sim = 0;
    table->all_threads_ready = 0;
    table->philos = s_malloc(sizeof(t_philo) * table->philo_num);
    s_mutex_handle(&table->table_mutex, INIT);
    table->forks = s_malloc(sizeof(t_fork) * table->philo_num);
    while(++i < table->philo_num)
    {
        s_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
    }
    philo_init(table);
}