/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:32:37 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/06 15:10:08 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_time(t_data *data)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	data->init_time.mu_s = tp.tv_usec;
	data->init_time.s = tp.tv_sec;
	data->t_begin_eat = get_time(data);
}

int	get_time(t_data *data)
{
	struct timeval	tp;
	int				time;

	if (gettimeofday(&tp, NULL))
		write(2, "GetTimeOfDay function error\n", 28);
	if (data->init_time.s == tp.tv_sec)
		time = (tp.tv_usec - data->init_time.mu_s) / 1000;
	else
	{
		time = (tp.tv_sec - (data->init_time.s + 1)) * 1000000;
		time += 1000000 - data->init_time.mu_s;
		time += tp.tv_usec;
		time /= 1000;
	}
	return (time);
}
