/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:38:27 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/04 15:36:13 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_data **data)
{
	int	time;

	time = get_time(data);
	(*data)->t_begin_sleep = time;
	if (!get_stop(data))
		write_msg(" is sleeping\n", data, time);
	while (!get_stop(data) && get_time(data) - (*data)->t_begin_sleep < \
	(*data)->arg->time_sleep)
		;
	time = get_time(data);
	if (!get_stop(data))
		write_msg(" is thinking\n", data, time);
}

void	philo_eat(t_data **data)
{
	int	time;

	time = get_time(data);
	set_eat(data, time, 0);
	if (!get_stop(data))
		write_msg(" is eating\n", data, time);
	while (!get_stop(data) && get_time(data) - get_eat(data, 0) < \
	(*data)->arg->time_eat)
		;
	// set_eat(data, 0, 1);
	if (pthread_mutex_unlock(&(*data)->info->forks[(*data)->index]) \
	|| pthread_mutex_unlock(&(*data)->info->forks[(*data)->next_circ->index]))
		write(2, "Pthread_Mutex_Unlock function error\n", 36);
	time = get_time(data);
	if (!get_stop(data))
		write_msg(" FINISH EATING\n", data, time);
}

void	philo_wait_forks(t_data **data)
{
	int	time;

	if (!get_stop(data) && \
	pthread_mutex_lock(&(*data)->info->forks[(*data)->index]))
		write(2, "Pthread_Mutex_Lock function error\n", 34);
	time = get_time(data);
	if (!get_stop(data))
		write_msg(" has taken a fork\n", data, time);
	else
	{
		if (pthread_mutex_unlock(&(*data)->info->forks[(*data)->index]))
			write(2, "Pthread_Mutex_Unlock function error\n", 36);
	}
	if (!get_stop(data) && \
	pthread_mutex_lock(&(*data)->info->forks[(*data)->next_circ->index]))
		write(2, "Pthread_Mutex_Lock function error\n", 34);
	time = get_time(data);
	if (!get_stop(data))
		write_msg(" has taken a fork\n", data, time);
	else
	{
		if (pthread_mutex_unlock(&(*data)->info->\
		forks[(*data)->next_circ->index]))
			write(2, "Pthread_Mutex_Unlock function error\n", 36);
	}
}

int	get_eat(t_data **data, int variable)
{
	int	getter;

	if (!variable)
	{
		if (pthread_mutex_lock(&(*data)->info->mutex_eat))
			write(2, "Pthread_Mutex_Lock function error\n", 34);
		getter = (*data)->t_begin_eat;
		if (pthread_mutex_unlock(&(*data)->info->mutex_eat))
			write(2, "Pthread_Mutex_Unlock function error\n", 36);
	}
	else
	{
		if (pthread_mutex_lock(&(*data)->info->mutex_nb_meals))
			write(2, "Pthread_Mutex_Lock function error\n", 34);
		getter = (*data)->nb_meals;
		if (pthread_mutex_unlock(&(*data)->info->mutex_nb_meals))
			write(2, "Pthread_Mutex_Unlock function error\n", 36);
	}
	return (getter);
}

void	set_eat(t_data **data, int nb, int variable)
{
	if (!variable)
	{
		if (pthread_mutex_lock(&(*data)->info->mutex_eat))
			write(2, "Pthread_Mutex_Lock function error\n", 34);
		(*data)->t_begin_eat = nb;
		if (pthread_mutex_unlock(&(*data)->info->mutex_eat))
			write(2, "Pthread_Mutex_Unlock function error\n", 36);
	}
	else
	{
		if (pthread_mutex_lock(&(*data)->info->mutex_nb_meals))
			write(2, "Pthread_Mutex_Lock function error\n", 34);
		(*data)->nb_meals += 1;
		if (pthread_mutex_unlock(&(*data)->info->mutex_nb_meals))
			write(2, "Pthread_Mutex_Unlock function error\n", 36);
	}
}
