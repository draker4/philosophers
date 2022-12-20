/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:23:19 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/20 17:25:58 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*start_routine(void *data)
{
	t_arg	*arg;

	arg = (t_arg *)data;
	while (1)
		printf("i = %d\n", arg->nb_philo);
	return (NULL);
}

static int	join_threads(t_arg arg, pthread_t *thread_philos)
{
	int	i;

	i = 0;
	while (i < arg.nb_philo)
	{
		if (pthread_join(thread_philos[i++], NULL))
			return (msg_error(4));
	}
	return (1);
}

static int	create_threads(t_arg arg, pthread_t *thread_philos)
{
	int	i;

	i = 0;
	while (i < arg.nb_total_philo)
	{
		printf("ici = %d\n", i);
		if (pthread_create(&thread_philos[i], NULL, &start_routine, &arg))
			return (msg_error(3));
		arg.nb_philo = i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_arg		arg;
	pthread_t	*thread_philos;

	if (argc != 5 && argc != 6)
		return (msg_error(1));
	arg = initialize(argc, argv);
	thread_philos = malloc(sizeof(pthread_t) * arg.nb_philo);
	if (!thread_philos)
		return (msg_error(2));
	if (!create_threads(arg, thread_philos) \
	|| !join_threads(arg, thread_philos))
	{
		free(thread_philos);
		return (0);
	}
	free(thread_philos);
	return (0);
}
