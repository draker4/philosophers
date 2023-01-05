/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:26:52 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/05 14:32:44 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "limits.h"
# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"

//structure saving the arguments of the program
typedef struct s_arg
{
	int	nb_total_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_min_eat;
}	t_arg;

//prototypes utils
int	ft_atoi(const char *str);

//prototypes message errors
int	msg_error(int msg, t_arg *arg, pid_t *pid);

#endif
