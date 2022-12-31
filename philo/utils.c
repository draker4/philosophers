/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperriol <bperriol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:31:06 by bperriol          #+#    #+#             */
/*   Updated: 2022/12/31 17:58:59 by bperriol         ###   ########lyon.fr   */
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

int	ft_atoi(const char *str)
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

void	write_msg(int msg, t_data **data, int time)
{
	if (msg == 0)
		printf("%d ms: %d has taken a fork\n", time, (*data)->index);
	else if (msg == 1)
	{
		(*data)->t_begin_eat = time;
		printf("%d ms: %d is eating\n", time, (*data)->index);
	}
	else if (msg == 2)
		printf("%d ms: %d is sleeping\n", time, (*data)->index);
	else if (msg == 3)
		printf("%d ms: %d is thinking\n", time, (*data)->index);
	else if (msg == 4)
	{
		(*data)->info->stop = 1;
		printf("%d ms: %d died\n", time, (*data)->index);
	}
}
