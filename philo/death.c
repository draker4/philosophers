/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:19:45 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/04 16:43:18 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_philo_dead(t_data **data, int time)
{
	int	error;
	int	i;

	error = 0;
	if (!get_eat(data, 0) && (*data)->arg->time_die <= time)
		error = 1;
	else if (time - get_eat(data, 0) >= (*data)->arg->time_die)
		error = 1;
	if (error)
	{
		if (pthread_mutex_lock(&(*data)->info->mutex_stop))
			write(2, "Pthread_Mutex_Lock function error\n", 34);
		if (!(*data)->info->stop)
			write_msg(" is dead\n", data, time);
		(*data)->info->stop = 1;
		if (pthread_mutex_unlock(&(*data)->info->mutex_stop))
			write(2, "Pthread_Mutex_Unlock function error\n", 36);
		i = 0;
		while (i < (*data)->arg->nb_total_philo)
			if (pthread_mutex_unlock(&(*data)->info->forks[i++]))
				write(2, "Pthread_Mutex_Unlock function error\n", 36);
	}
}

static void	has_enough_eat(t_data **data)
{
	int	i;

	set_stop(data, 1);
	i = 0;
	while (i < (*data)->arg->nb_total_philo)
	{
		if (pthread_mutex_unlock(&(*data)->info->forks[i++]))
			write(2, "Pthread_Mutex_Unlock function error\n", 36);
	}
}

void	check_death(t_data **data)
{
	t_data	*current;
	int		nb_meals;
	int		time;

	while (get_stop(data) <= 0)
	{
		nb_meals = 1;
		current = *data;
		while (current)
		{
			time = get_time(data);
			is_philo_dead(&current, time);
			if ((*data)->arg->nb_min_eat > 0 && \
			get_eat(&current, 1) < (*data)->arg->nb_min_eat)
				nb_meals = 0;
			current = current->next;
		}
		if ((*data)->arg->nb_min_eat > 0 && nb_meals)
			has_enough_eat(data);
	}
}

int	get_stop(t_data **data)
{
	int	stop;

	if (pthread_mutex_lock(&(*data)->info->mutex_stop))
		write(2, "Pthread_Mutex_Lock function error\n", 34);
	stop = (*data)->info->stop;
	if (pthread_mutex_unlock(&(*data)->info->mutex_stop))
		write(2, "Pthread_Mutex_Unlock function error\n", 36);
	return (stop);
}

void	set_stop(t_data **data, int nb)
{
	if (pthread_mutex_lock(&(*data)->info->mutex_stop))
		write(2, "Pthread_Mutex_Lock function error\n", 34);
	(*data)->info->stop = nb;
	if (pthread_mutex_unlock(&(*data)->info->mutex_stop))
		write(2, "Pthread_Mutex_Unlock function error\n", 36);
}
