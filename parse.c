#include "philo.h"
#include <stdio.h>
# include <stdlib.h>
# include <limits.h>

static long ft_atol(const char *str)
{
    long    retval;

    retval = 0;
    while (*str == ' ' || *str == '\t' || *str == '\n'
        || *str == '\v' || *str == '\f' || *str == '\r')
        str++;
    if(*str == '+')
        str++;
    if (*str == '-')
        error_exit("Give me only positive numbers you smart creature");
    if (*str < '0' || *str > '9')
        error_exit("Give me only numbers you smart creature");
    while (*str >= '0' && *str <= '9')
    {
        retval = retval * 10 + (*str - '0');
        str++;
    }
    if (retval > INT_MAX)
        error_exit("Give me a number between 0 and 2147483647 you smart creature");
    return (retval);
}

void    parse_input(t_table *table, char **av)
{
    table->philo_num = ft_atol(av[1]);
    table->time_to_die = ft_atol(av[2]) * 1e3;
    table->time_to_eat = ft_atol(av[3]) * 1e3;
    table->time_to_sleep = ft_atol(av[4]) * 1e3;
    if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 || table->time_to_sleep < 6e4)
        error_exit("Give me more time, at least more than 60ms you smart creature");
    if (av[5])
        table->num_limit_meals = ft_atol(av[5]);
    else
        table->num_limit_meals = -1;
}