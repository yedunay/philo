/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydunay <ydunay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:38:59 by ydunay            #+#    #+#             */
/*   Updated: 2024/07/03 15:33:02 by ydunay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void	*s_malloc(size_t size)
{
	void	*rt;

	rt = malloc(size);
	if (!rt)
	{
		printf("Malloc problems !\
			This time it's not about you smart creature");
		return (NULL);
	}
	return (rt);
}

static int	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (true);
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		return (error_exit("The value specified by mutex is invalid"));
	else if (status == EINVAL && opcode == INIT)
		return (error_exit("The value specified by attr is invalid"));
	else if (status == EDEADLK)
		return (error_exit("A deadlock would accur \
			if the thread blocked waiting for mutex."));
	else if (status == EPERM)
		return (error_exit("The current thread does not hold a lock on mutex"));
	else if (status == ENOMEM)
		return (error_exit("The process cannot allocate \
			enough memory to create another mutex"));
	else if (status == EBUSY)
		return (error_exit("Mutex is locked"));
	return (true);
}

int	s_mutex_handle(t_mtx *mtx, t_opcode opcode)
{
	if (opcode == LOCK)
	{
		if (handle_mutex_error(pthread_mutex_lock(mtx), opcode) == -42)
			return (-42);
	}
	else if (opcode == UNLOCK)
	{
		if (handle_mutex_error(pthread_mutex_unlock(mtx), opcode) == -42)
			return (-42);
	}
	else if (opcode == INIT)
	{
		if (handle_mutex_error(pthread_mutex_init(mtx, NULL), opcode) == -42)
			return (-42);
	}
	else if (opcode == DESTROY)
	{
		if (handle_mutex_error(pthread_mutex_destroy(mtx), opcode) == -42)
			return (-42);
	}
	else
		return (error_exit("Wrong operation code for mutex handle"));
	return (true);
}

static int	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (true);
	if (status == EAGAIN)
		return (error_exit("No resources to create another thread"));
	else if (status == EPERM)
		return (error_exit("The caller doesn't have appropriate permission\n"));
	else if (status == EINVAL && opcode == CREATE)
		return (error_exit("The value specified by attr is invalid."));
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		return (error_exit("The value specified by thread is not joinable\n"));
	else if (status == ESRCH)
		return (error_exit("No thread could be found corresponding to that \
			specified by the given thread ID, thread."));
	else if (status == EDEADLK)
		return (error_exit("A deadlock was detected or the value of \
			thread specifies the calling thread."));
	return (true);
}

int	s_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	if (opcode == CREATE)
	{
		if (handle_thread_error(pthread_create(thread, NULL, foo, data),
				opcode) == -42)
			return (-42);
	}
	else if (opcode == JOIN)
	{
		if (handle_thread_error(pthread_join(*thread, NULL), opcode) == -42)
			return (-42);
	}
	else if (opcode == DETACH)
	{
		if (handle_thread_error(pthread_detach(*thread), opcode) == -42)
			return (-42);
	}
	else
		return (error_exit("Wrong opcode for thread_handle:\
			 use <CREATE> <JOIN> <DETACH>"));
	return (true);
}
