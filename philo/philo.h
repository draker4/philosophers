/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:22:36 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/20 16:04:59 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>

typedef struct s_arg
{
	int	nb_total_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_times_eat;
	int	nb_philo;
}	t_arg;

//prototypes utils
t_arg	initialize(int argc, char **argv);

//prototypes message error
int		msg_error(int msg);

#endif
