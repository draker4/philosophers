/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:31:06 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/20 16:05:15 by bperriol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_overflow(int sign)
{
	if (sign < 0)
		return ((int)LONG_MIN);
	else
		return ((int)LONG_MAX);
}

static int	ft_atoi(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result != (result * 10 + str[i] - 48) / 10)
			return (ft_overflow(sign));
		else
			result = result * 10 + str[i] - 48;
		i++;
	}
	return ((int)(result * sign));
}

t_arg	initialize(int argc, char **argv)
{
	t_arg	arg;

	arg.nb_philo = 0;
	arg.nb_total_philo = ft_atoi(argv[1]);
	arg.time_die = ft_atoi(argv[2]);
	arg.time_eat = ft_atoi(argv[3]);
	arg.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg.nb_times_eat = ft_atoi(argv[5]);
	else
		arg.nb_times_eat = 0;
	return (arg);
}
