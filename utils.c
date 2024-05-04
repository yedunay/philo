/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:12:43 by ydunay            #+#    #+#             */
/*   Updated: 2024/05/04 18:04:16 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

long    get_time(t_time_code time_code)
{
    struct timeval  tv;
    
    if(gettimeofday(&tv, NULL))
        error_exit("gettimeofdayfunction screwed up");
    if(time_code == SEC)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if(time_code == MSEC)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if(time_code == USEC)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Wrong input for gettime");
    return (424242);
}

void    precise_usleep(long time, t_table *table)
{
    long    start;
    long    rem;
    long    elapsed;
    
    start = get_time(MSEC);
    while(get_time(MSEC) - start < time)
    {
        if(sim_finished(table))
            break ;
        elapsed = get_time(MSEC) - start;
        rem = time - elapsed;
        if(rem > 1e3)
            usleep(rem / 2);
        else
            while(get_time(MSEC) - start < time)
                ;
    }
    
}

void    error_exit(const char *error)
{
    printf(RED "! %s !" RESET "\n", error);
    exit(EXIT_FAILURE);
}