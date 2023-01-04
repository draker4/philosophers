/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:52:46 by bperriol          #+#    #+#             */
/*   Updated: 2023/01/04 15:29:32 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fill_arg(t_arg *arg, int argc, char **argv)
{
	arg->nb_total_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->nb_min_eat = ft_atoi(argv[5]);
	else
		arg->nb_min_eat = 0;
}

// static void	fill_info(t_info *info, pthread_mutex_t	*forks, \
// pthread_mutex_t	*neighbourgs, pthread_mutex_t *mutex_stop)
// {
// 	info->stop = -1;
// 	info->init_time.s = 0;
// 	info->init_time.mu_s = 0;
// 	info->forks = forks;
// 	info->neighbourgs = neighbourgs;
// 	info->mutex_stop = mutex_stop;
// }

static int	free_all(t_arg *arg, t_info *info, pthread_mutex_t *forks)
{
	free(arg);
	free(info);
	if (forks)
		free(forks);
	return (msg_error(2, NULL));
}

static int	init_arg_info(t_arg *arg, t_info *info, int argc, char **argv)
{
	pthread_mutex_t	*forks;

	fill_arg(arg, argc, argv);
	forks = malloc(sizeof(pthread_mutex_t) * arg->nb_total_philo);
	if (!forks)
		return (free_all(arg, info, NULL));
	info->stop = -1;
	info->init_time.s = 0;
	info->init_time.mu_s = 0;
	info->forks = forks;
	return (1);
}

int	initialize(t_data **data, int argc, char **argv)
{
	t_arg			*arg;
	t_info			*info;

	if (argc != 5 && argc != 6)
		return (msg_error(1, NULL));
	if (ft_atoi(argv[1]) < 1)
		return (msg_error(3, NULL));
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (msg_error(0, NULL));
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (msg_error(2, NULL));
	info = malloc(sizeof(t_info));
	if (!info)
		return (free(arg), msg_error(2, NULL));
	if (!init_arg_info(arg, info, argc, argv))
		return (0);
	if (!create_lst_data(data, arg, info))
		return (0);
	return (1);
}
