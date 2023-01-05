/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:27:28 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/05 14:36:27 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	initialize(t_arg *arg, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (msg_error(1, NULL, NULL));
	if (ft_atoi(argv[1]) < 1)
		return (msg_error(3, NULL, NULL));
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (msg_error(0, NULL, NULL));
	arg->nb_total_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->nb_min_eat = ft_atoi(argv[5]);
	else
		arg->nb_min_eat = 0;
	return (1);
}

static int	create_philos(t_arg *arg)
{
	int		i;
	pid_t	*pid;
	pid_t	id;

	i = 0;
	pid = malloc(sizeof(pid_t) * arg->nb_total_philo);
	if (!pid)
		return (msg_error(2, arg, NULL));
	// pid[i] = fork();
	// if (pid[i] == -1)
	// 	return (msg_error(4, arg, pid));
	while (i < arg->nb_total_philo)
	{
		if (pid[i] > 0)
			id = fork();
		if (id == -1)
			return (msg_error(4, arg, pid));
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (msg_error(2, NULL, NULL));
	if (!initialize(arg, argc, argv))
		return (0);
	if (!create_philos(arg))
		return (0);
	printf("hello_world !\n");
}
