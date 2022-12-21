/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:23:19 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/21 18:59:17 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*start_routine(void *data)
{
	int	index;
	int	*result;

	index = *(int *)data;
	free(data);
	result = malloc(sizeof(int *));
	*result = index;
	printf("i = %d\n", index);
	return ((void *)result);
}

static int	join_threads(t_arg *arg, pthread_t *thread_philos)
{
	int	i;
	int	*res;

	i = 0;
	while (i < arg->nb_philo)
	{
		if (pthread_join(thread_philos[i++], (void **)&res))
		{
			free(res);
			return (msg_error(4));
		}
		printf("fin index = %d\n", *res);
		free(res);
	}
	return (1);
}

static int	create_threads(t_arg *arg, pthread_t *philos)
{
	int	i;
	int	*index;

	i = 0;
	while (i < arg->nb_total_philo)
	{
		index = malloc(sizeof(int *));
		*index = i;
		if (pthread_create(&philos[i], NULL, &start_routine, index))
			return (msg_error(3));
		arg->nb_philo = i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_arg		arg;
	pthread_t	*philos;

	if (!initialize(&arg, argc, argv))
		return (0);
	philos = malloc(sizeof(pthread_t) * arg.nb_philo);
	if (!philos)
		return (msg_error(2));
	if (!create_threads(&arg, philos) || !join_threads(&arg, philos))
		return (0);
	free(philos);
	return (0);
}
