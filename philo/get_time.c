/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:50:52 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/31 18:45:34 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_philo_dead(t_data **data, int time)
{
	int	error;
	int	i;

	error = 0;
	if (!(*data)->t_begin_eat && (*data)->arg->time_die <= time)
		error = 1;
	else if (time - (*data)->t_begin_eat >= (*data)->arg->time_die)
		error = 1;
	if (error)
	{
		(*data)->info->stop = 1;
		write_msg(4, data, time);
		i = 0;
		while (i < (*data)->arg->nb_total_philo)
			if (pthread_mutex_unlock(&(*data)->info->forks[i]) && \
			pthread_mutex_unlock(&(*data)->info->neighbourgs[i++]))
				write(2, "Pthread_Mutex_Unlock function error\n", 34);
	}
}

int	get_time(t_data **data)
{
	struct timeval	tp;
	int				time;

	if (gettimeofday(&tp, NULL))
		write(2, "GetTimeOfDay function error\n", 28);
	if (!(*data)->info->init_time.s)
	{
		(*data)->info->init_time.s = tp.tv_sec;
		(*data)->info->init_time.mu_s = tp.tv_usec;
	}
	if ((*data)->info->init_time.s == tp.tv_sec)
		time = tp.tv_usec - (*data)->info->init_time.mu_s;
	else
	{
		time = (tp.tv_sec - (*data)->info->init_time.s + 1) * 1000000;
		time += 1000000 - tp.tv_usec;
		time += (*data)->info->init_time.mu_s;
		if (time)
			time /= 1000;
	}
	printf("timeday = %ld et %ld\n", tp.tv_sec, tp.tv_usec);
	printf("time init = %d et %d\n", (*data)->info->init_time.s, (*data)->info->init_time.mu_s);
	is_philo_dead(data, time);
	return (time);
}
