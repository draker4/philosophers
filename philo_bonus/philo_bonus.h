/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:26:52 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/06 17:03:54 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_time
{
	int	s;
	int	mu_s;
}	t_time;

//structure saving the arguments of the program
typedef struct s_arg
{
	int	nb_total_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_min_eat;
}	t_arg;

//structure saving all data for each philosopher
typedef struct s_data
{
	t_arg	*arg;
	pid_t	*pid_tab;
	t_time	init_time;
	sem_t	*sem;
	sem_t	*sem_write;
	sem_t	*sem_stop;
	sem_t	*sem_meals;
	int		index;
	int		t_begin_eat;
	int		t_begin_sleep;
	int		nb_meals;
	int		send_stop;
}	t_data;

//prototypes utils
int		ft_atoi(const char *str);
void	write_msg(char *str, t_data *data, int time, int death);

//prototypes message errors
int		msg_error(int msg, t_data *data);

//prototypes initiatization
int		initialize(t_data *data, int argc, char **argv);

//prototypes get time
int		get_time(t_data *data);
void	init_time(t_data *data);

//prototypes putstr
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_strlen(char *s);

//prototypes philosophers actions
void	philo_wait_forks(t_data *data);
void	philo_eat(t_data *data);
void	philo_sleep(t_data *data);
int		is_not_dead(t_data *data, int time);
void	philo_one_fork(t_data *data);

#endif
