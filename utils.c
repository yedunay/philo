/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:12:43 by ydunay            #+#    #+#             */
/*   Updated: 2024/05/03 15:23:13 by ydunay           ###   ########.fr       */
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
        return (tv.tv_sec + (tv.tv_sec / 1e6));
    else if(time_code == MSEC)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if(time_code == USEC)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        error_exit("Wrong input for gettime");
    return (424242);
}

void    error_exit(const char *error)
{
    printf(RED "! %s !" RESET "\n", error);
    exit(EXIT_FAILURE);
}