#include "philo.h"

void    *dinner_sim(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *)data;
    wait_all_threads(philo->table);

}

void    dinner_start(t_table *table)
{
    int i;

    i  = -1;
    if(table->num_limit_meals == 0)
        return ;
    else if(table->num_limit_meals == 1)
        ;
    else
    {
        while(++i < table->philo_num)
            s_thread_handle(&table->philos[i].thread_id, dinner_sim, &table->philos[i], CREATE);
    }
    table->start_sim = get_time(MSEC);
    set_bin(&table->table_mutex, &table->all_threads_ready, 1);
    i = -1;
    while(++i < table->philo_num)
        s_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
}