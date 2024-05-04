#include "philo.h"
#include <errno.h>

void	*s_malloc(size_t size)
{
	void	*rt;

	rt = malloc(size);
	if (!rt)
		error_exit("Malloc problems ! This time it's not about you smart creature");
	return (rt);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("A deadlock would accur if the thread blocked waiting for mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate enough memory to create another mutex");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	s_mutex_handle(t_mtx *mtx, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mtx), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mtx), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mtx, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mtx), opcode);
	else
		error_exit("Wrong operation code for mutex handle");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission\n");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that"
					"specified by the given thread ID, thread.");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of"
					"thread specifies the calling thread.");
}
void    s_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
	t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle:"
            " use <CREATE> <JOIN> <DETACH>");
}
