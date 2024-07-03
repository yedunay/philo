/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:39:10 by ydunay            #+#    #+#             */
/*   Updated: 2024/07/03 15:29:52 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static long	ft_atol2(const char *str, long retval)
{
	int	i;

	i = 0;
	while (*str >= '0' && *str <= '9')
	{
		retval = retval * 10 + (*str - '0');
		str++;
	}
	if (retval > INT_MAX)
	{
		printf("Give me a number between 0\
			and 2147483647 you smart creature");
		return (-42);
	}
	while (str[i] != '\0' && (str[i] < '0' || str[i++] > '9'))
	{
		printf("Give me only numbers you smart creature");
		return (-42);
	}
	return (retval);
}

static long	ft_atol(const char *str)
{
	long	retval;

	retval = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	if (*str == '-')
	{
		printf("Give me only positive numbers you smart creature");
		return (-42);
	}
	if (*str < '0' || *str > '9')
	{
		printf("Give me only numbers you smart creature");
		return (-42);
	}
	retval = ft_atol2(str, retval);
	return (retval);
}

static int	parse_input2(t_table *table, char **av)
{
	if (table->philo_num != -42 && ((table->time_to_die != -42000
				&& table->time_to_die < 6e4) || (table->time_to_eat != -42000
				&& table->time_to_eat < 6e4) || (table->time_to_sleep < 6e4
				&& table->time_to_sleep != -42000)))
	{
		printf(" Give me more time,\
			at least more than 60ms you smart creature");
		return (-42);
	}
	if (av[5])
	{
		table->num_limit_meals = ft_atol(av[5]);
		if (table->num_limit_meals == -42)
			return (-42);
	}
	else
		table->num_limit_meals = -1;
	return (0);
}

int	parse_input(t_table *table, char **av)
{
	table->philo_num = ft_atol(av[1]);
	if (table->philo_num == -42)
		return (-42);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	if (table->time_to_die == -42000)
		return (-42);
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	if (table->time_to_eat == -42000)
		return (-42);
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_sleep == -42000)
		return (-42);
	if (parse_input2(table, av) == -42)
		return (-42);
	return (0);
}
