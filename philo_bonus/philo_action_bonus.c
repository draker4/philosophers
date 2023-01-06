/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:53:50 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/06 17:03:48 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_not_dead(t_data *data, int time)
{
	if (time - data->t_begin_eat >= data->arg->time_die)
		return (0);
	if (data->arg->nb_min_eat && data->nb_meals == data->arg->nb_min_eat \
	&& data->send_stop)
	{
		data->send_stop = 0;
		if (sem_post(data->sem_meals))
			write(2, "Sem_post function error!\n", 25);
	}
	return (1);
}

void	philo_sleep(t_data *data)
{
	int	time;

	time = get_time(data);
	if (is_not_dead(data, time))
		write_msg(" is sleeping\n", data, time, 0);
	data->t_begin_sleep = time;
	while (is_not_dead(data, time) && \
	time - data->t_begin_sleep < data->arg->time_sleep)
	{
		usleep(500);
		time = get_time(data);
	}
	if (is_not_dead(data, time))
		write_msg(" is thinking\n", data, time, 0);
}

void	philo_eat(t_data *data)
{
	int	time;

	time = get_time(data);
	if (is_not_dead(data, time))
		write_msg(" is eating\n", data, time, 0);
	data->t_begin_eat = time;
	while (is_not_dead(data, time) && \
	time - data->t_begin_eat < data->arg->time_eat)
	{
		usleep(500);
		time = get_time(data);
	}
	data->nb_meals += 1;
	if (sem_post(data->sem))
		write(2, "Sem_post function error!\n", 25);
	if (sem_post(data->sem))
		write(2, "Sem_post function error!\n", 25);
}

void	philo_one_fork(t_data *data)
{
	int	time;

	if (sem_wait(data->sem))
		write(2, "Sem_wait function error!\n", 25);
	time = get_time(data);
	if (is_not_dead(data, time))
		write_msg(" has taken a fork\n", data, time, 0);
}

void	philo_wait_forks(t_data *data)
{
	int	time;
	int	twice;

	twice = 2;
	while (twice--)
	{
		if (sem_wait(data->sem))
			write(2, "Sem_wait function error!\n", 25);
		time = get_time(data);
		if (is_not_dead(data, time))
			write_msg(" has taken a fork\n", data, time, 0);
	}
}
