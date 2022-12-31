/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:23:19 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/31 18:49:19 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *p_data)
{
	t_data			*data;

	data = (t_data *)p_data;
	while (data->info->stop == -1)
		;
	while (!data->info->stop)
	{
		philo_wait_forks(&data, data->index, data->prev_circ->index);
		if (data->arg->nb_total_philo > 1 && !data->info->stop)
			philo_wait_forks(&data, data->next_circ->index, \
			data->next_circ->index);
		if (!data->info->stop)
			philo_eat(&data);
	}
	return (data);
}

static int	join_threads(t_data *data, pthread_t *philos)
{
	int		i;
	t_data	*res;

	i = 0;
	while (i < data->arg->nb_total_philo)
	{
		if (pthread_join(philos[i], (void **)&res))
			write(2, "Pthread_join function error!\n", 29);
		i++;
	}
	return (1);
}

static int	create_threads(t_data *data, pthread_t *philos)
{
	int		i;
	t_data	*current;

	i = 0;
	current = data;
	while (i < data->arg->nb_total_philo)
	{
		if (pthread_create(&philos[i], NULL, &routine, (void *)current))
			write(2, "Pthread_create function error!\n", 31);
		current = current->next;
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			*data;
	pthread_t		*philos;

	data = NULL;
	if (!initialize(&data, argc, argv) || !init_mutex(&data))
		return (0);
	philos = malloc(sizeof(pthread_t) * data->arg->nb_total_philo);
	if (!philos)
		return (msg_error(2, NULL, &data));
	create_threads(data, philos);
	data->info->stop = 0;
	join_threads(data, philos);
	return (msg_error(0, philos, &data));
}
