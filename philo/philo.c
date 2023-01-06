/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:23:19 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/06 16:48:36 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *p_data)
{
	t_data	*data;

	data = (t_data *)p_data;
	set_begin(&data);
	while (get_stop(&data) == -1)
		;
	if (data->index % 2)
		usleep(500);
	while (!get_stop(&data))
	{
		philo_wait_forks(&data);
		if (!get_stop(&data))
			philo_eat(&data);
		if (!get_stop(&data))
			philo_sleep(&data);
	}
	return (data);
}

static int	join_threads(t_data **data)
{
	int		i;
	t_data	*res;

	i = 0;
	while (i < (*data)->arg->nb_total_philo)
	{
		if (pthread_join((*data)->info->philos[i], (void **)&res))
			write(2, "Pthread_join function error!\n", 29);
		i++;
	}
	return (1);
}

static int	create_threads(t_data **data)
{
	int		i;
	t_data	*current;

	i = 0;
	current = *data;
	while (i < (*data)->arg->nb_total_philo)
	{
		if (pthread_create(&(*data)->info->philos[i], \
		NULL, &routine, (void *)current))
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
	struct timeval	tp;

	data = NULL;
	if (!initialize(&data, argc, argv) || !init_mutex(&data))
		return (0);
	philos = malloc(sizeof(pthread_t) * data->arg->nb_total_philo);
	if (!philos)
		return (msg_error(2, &data));
	data->info->philos = philos;
	create_threads(&data);
	while (get_begin(&data) != data->arg->nb_total_philo)
		;
	if (gettimeofday(&tp, NULL))
		write(2, "GetTimeOfDay function error\n", 28);
	data->info->init_time.s = tp.tv_sec;
	data->info->init_time.mu_s = tp.tv_usec;
	set_stop(&data, 0);
	check_death(&data);
	join_threads(&data);
	return (msg_error(0, &data));
}
