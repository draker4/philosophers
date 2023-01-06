/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:23:50 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/06 16:31:22 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_arg(t_arg *arg, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (msg_error(1, NULL));
	if (ft_atoi(argv[1]) < 1)
		return (msg_error(3, NULL));
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (msg_error(0, NULL));
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

static int	init_data(t_data *data)
{
	sem_t	*sem;
	sem_t	*sem_write;
	sem_t	*sem_stop;
	sem_t	*sem_meals;

	sem = sem_open("/sem_forks", O_CREAT, 0644, data->arg->nb_total_philo);
	sem_write = sem_open("/sem_write", O_CREAT, 0644, 1);
	sem_stop = sem_open("/sem_stop", O_CREAT, 0644, 0);
	sem_meals = sem_open("/sem_meals", O_CREAT, 0644, 0);
	data->sem = sem;
	data->sem_write = sem_write;
	data->sem_stop = sem_stop;
	data->sem_meals = sem_meals;
	if (sem == SEM_FAILED || sem_write == SEM_FAILED || sem_stop == SEM_FAILED \
	|| sem_meals == SEM_FAILED)
		return (msg_error(2, data));
	if (sem_unlink("/sem_forks") || sem_unlink("/sem_write") \
	|| sem_unlink("/sem_stop") || sem_unlink("/sem_meals"))
		return (msg_error(7, data));
	return (1);
}

static void	init_data_null(t_data *data)
{
	data->t_begin_eat = 0;
	data->t_begin_sleep = 0;
	data->index = 0;
	data->nb_meals = 0;
	data->send_stop = 1;
	data->sem = NULL;
	data->sem_stop = NULL;
	data->sem_write = NULL;
	data->sem_meals = NULL;
	data->arg = NULL;
	data->pid_tab = NULL;
}

int	initialize(t_data *data, int argc, char **argv)
{
	t_arg	*arg;
	pid_t	*pid_tab;

	init_data_null(data);
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (msg_error(2, data));
	data->arg = arg;
	if (!init_arg(arg, argc, argv))
		return (msg_error(0, data));
	pid_tab = malloc(sizeof(pid_t) * arg->nb_total_philo + 1);
	if (!pid_tab)
		return (msg_error(2, data));
	data->pid_tab = pid_tab;
	if (!init_data(data))
		return (0);
	return (1);
}
