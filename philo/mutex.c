/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:10:43 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/04 15:29:56 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data **data)
{
	int				i;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_nb_meals;

	i = 0;
	if (pthread_mutex_init(&mutex_stop, NULL) || \
	pthread_mutex_init(&mutex_write, NULL) || \
	pthread_mutex_init(&mutex_eat, NULL) || \
	pthread_mutex_init(&mutex_nb_meals, NULL))
		return (msg_error(4, data));
	while (i < (*data)->arg->nb_total_philo)
		if (pthread_mutex_init(&(*data)->info->forks[i++], NULL))
			return (msg_error(4, data));
	(*data)->info->mutex_stop = mutex_stop;
	(*data)->info->mutex_write = mutex_write;
	(*data)->info->mutex_eat = mutex_eat;
	(*data)->info->mutex_nb_meals = mutex_nb_meals;
	return (1);
}

void	destroy_mutex(t_data **data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&(*data)->info->mutex_stop) || \
	pthread_mutex_destroy(&(*data)->info->mutex_write) || \
	pthread_mutex_destroy(&(*data)->info->mutex_eat) || \
	pthread_mutex_destroy(&(*data)->info->mutex_nb_meals))
		write(2, "Pthread_Mutex_Destroy function error\n", 37);
	while (i < (*data)->arg->nb_total_philo)
		if (pthread_mutex_destroy(&(*data)->info->forks[i++]))
			write(2, "Pthread_Mutex_Destroy function error\n", 37);
}
