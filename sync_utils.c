#include "philo.h"

void    wait_all_threads(t_table *table)
{
    while(!get_bin(&table->table_mutex, &table->all_threads_ready))
        ;
}