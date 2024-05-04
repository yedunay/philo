#ifndef PHILO_H
# define PHILO_H
# include <stdbool.h>
# include <pthread.h>

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

# ifndef PHILO_MAX
#  define PHILO_MAX 200 
# endif

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;


typedef enum e_time_code
{
	SECONDS,
	MSEC,
	USEC,
}		t_time_code;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

# define RESET    "\033[0m"      
# define RED	"\033[1;31m"  
# define GREEN      "\033[1;32m"  

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;
typedef struct s_fork
{
	t_mtx		fork;
	int			fork_id;
}				t_fork;

typedef struct s_philo
{
	int				id;
	bool			full;
	long			meals_counter;
	long			last_meal_time;
	pthread_t		thread_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_mtx			philo_mutex;
	t_table			*table;
}				t_philo;

struct	s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_limit_meals;
	long				philo_num;
	long				start_sim;
	bool				end_sim;
	bool				all_threads_ready;
	long				threads_running_num;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
};

void	s_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
void	s_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	*s_malloc(size_t bytes);

void	parse_input(t_table *table, char **av);

void	data_init(t_table *table);

void	dinner_start(t_table *table);

void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	sim_finished(t_table *table);

time_t	gettime(int time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);
void	error_exit(const char *error);

void	write_status(t_philo_status status, t_philo *philo, bool debug);

void	wait_all_threads(t_table *table);
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_num);
void    thinking(t_philo *philo, bool pre_sim);
void    de_synchronize_philos(t_philo *philo);

void	*monitor_dinner(void *data);

#endif
