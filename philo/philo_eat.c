/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:38:27 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/31 18:59:58 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_data **data)
{
	int	time;

	time = get_time(data);
	if (!(*data)->info->stop)
		write_msg(1, data, time);
	while (!(*data)->info->stop && get_time(data) - (*data)->t_begin_eat < \
	(*data)->arg->time_eat)
		;
	if (pthread_mutex_unlock(&(*data)->info->neighbourgs[(*data)->index]) && \
		pthread_mutex_unlock(&(*data)->info->forks[(*data)->index]))
		write(2, "Pthread_Mutex_Unlock function error\n", 34);
	if (pthread_mutex_unlock(&(*data)->info->neighbourgs \
	[(*data)->next_circ->index]) \
	&& pthread_mutex_unlock(&(*data)->info->forks[(*data)->next_circ->index]))
		write(2, "Pthread_Mutex_Unlock function error\n", 34);
}

void	philo_wait_forks(t_data **data, int index, int neighbourg)
{
	int	time;

	write(1, "waiting fork=", 13);
	ft_putnbr_fd((*data)->index, 1);
	write(1, "\n", 1);
	if (!(*data)->info->stop && \
	pthread_mutex_lock(&(*data)->info->neighbourgs[neighbourg]) && \
	pthread_mutex_lock(&(*data)->info->forks[index]))
		write(2, "Pthread_Mutex_Lock function error\n", 34);
	time = get_time(data);
	if (!(*data)->info->stop)
		write_msg(0, data, time);
	else
	{
		if (pthread_mutex_unlock(&(*data)->info->neighbourgs[neighbourg]) && \
		pthread_mutex_unlock(&(*data)->info->forks[index]))
			write(2, "Pthread_Mutex_Unlock function error\n", 34);
	}
}
