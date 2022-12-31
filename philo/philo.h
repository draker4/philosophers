/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:22:36 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/31 18:44:12 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
#include <stdio.h>

// vector saving tim in seconds and microseconds
typedef struct s_vector
{
	int	s;
	int	mu_s;
}	t_vector;

//structure saving the arguments of the program
typedef struct s_arg
{
	int	nb_total_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_min_eat;
}	t_arg;

//structure that all can access directly in the linked list
typedef struct s_info
{
	int				stop;
	t_vector		init_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*neighbourgs;
}	t_info;

//structure for each philo (linked list)
typedef struct s_data
{
	int				index;
	int				nb_times_eat;
	int				t_begin_eat;
	int				has_one_fork;
	t_info			*info;
	t_arg			*arg;
	struct s_data	*next;
	struct s_data	*prev_circ;
	struct s_data	*next_circ;
}	t_data;

//prototypes utils
int		ft_atoi(const char *str);
void	write_msg(int msg, t_data **data, int time);

//prototypes init
int		initialize(t_data **data, int argc, char **argv);
int		create_lst_data(t_data **data, t_arg *arg, t_info *info);

//prototypes init_list
int		init_mutex(t_data **data);

//prototypes message error and free all
int		msg_error(int msg, pthread_t *philos, t_data **data);

//prototypes linked list
t_data	*create_new(int index, t_arg *arg, t_info *info);
void	lst_add_back(t_data **data, t_data *to_add);
void	lst_clear(t_data **data);

//prorotypes philo_eat
void	philo_wait_forks(t_data **data, int index, int neighbourg);
void	philo_eat(t_data **data);

//prototypes get_time
int		get_time(t_data **data);
void	*routine_time(void *p_data);

//prototypes putstr
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
