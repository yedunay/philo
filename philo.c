/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:39:17 by ydunay            #+#    #+#             */
/*   Updated: 2024/07/03 15:30:26 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	freephilos(t_table *table)
{
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (parse_input(&table, av) == -42)
			return (-42);
		if (data_init(&table) == -42)
			return (freephilos(&table), -42);
		if (dinner_start(&table) == -42)
			return (clean(&table), -42);
		clean(&table);
	}
	else
		printf("Wrong input :\n" GREEN "Correct is ./philo 5 800 200 200 [5]");
}
