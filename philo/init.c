/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 14:52:46 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/31 18:53:04 by bperriol         ###   ########lyon.fr   */
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
		arg->nb_min_eat = -1;
}

static void	fill_info(t_info *info, pthread_mutex_t	*forks, \
pthread_mutex_t	*neighbourgs)
{
	info->stop = -1;
	info->init_time.s = 0;
	info->init_time.mu_s = 0;
	info->forks = forks;
	info->neighbourgs = neighbourgs;
}

static int	init_arg_info(t_arg *arg, t_info *info, int argc, char **argv)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*neighbourgs;

	fill_arg(arg, argc, argv);
	forks = malloc(sizeof(pthread_mutex_t) * arg->nb_total_philo);
	if (!forks)
		return (free(arg), free(info), msg_error(2, NULL, NULL));
	neighbourgs = malloc(sizeof(pthread_mutex_t) * arg->nb_total_philo);
	if (!neighbourgs)
		return (free(arg), free(info), free(forks), msg_error(2, NULL, NULL));
	fill_info(info, forks, neighbourgs);
	return (1);
}

int	initialize(t_data **data, int argc, char **argv)
{
	t_arg			*arg;
	t_info			*info;

	if (argc != 5 && argc != 6)
		return (msg_error(1, NULL, NULL));
	if (ft_atoi(argv[1]) < 1)
		return (msg_error(3, NULL, NULL));
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (msg_error(2, NULL, NULL));
	info = malloc(sizeof(t_info));
	if (!info)
		return (free(arg), msg_error(2, NULL, NULL));
	if (!init_arg_info(arg, info, argc, argv))
		return (0);
	if (!create_lst_data(data, arg, info))
		return (0);
	return (1);
}
