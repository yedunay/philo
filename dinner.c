#include "philo.h"

static void thinking(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);
}

static void eat(t_philo *philo)
{
    s_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    s_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MSEC));
    philo->meals_counter++;
    write_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->table->time_to_eat, philo->table);
    if(philo->table->num_limit_meals > 0 && philo->meals_counter == philo->table->num_limit_meals)
        set_bin(&philo->philo_mutex, &philo->full, 1);
    s_mutex_handle(&philo->first_fork->fork, UNLOCK);
    s_mutex_handle(&philo->second_fork->fork, UNLOCK);

}

void    *dinner_sim(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *)data;
    wait_all_threads(philo->table);

    while (!sim_finished(philo->table))
    {
        if (philo->full)
            break ;
        eat(philo);
        write_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->table->time_to_sleep, philo->table);
        thinking(philo);
    }
    return (NULL);
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
        while(++i < table->philo_num)
        {
            s_thread_handle(&table->philos[i].thread_id, dinner_sim, &table->philos[i], CREATE);
        }
    table->start_sim = get_time(MSEC);
    set_bin(&table->table_mutex, &table->all_threads_ready, 1);
    i = -1;
    while(++i < table->philo_num)
    {
        s_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
    }
}